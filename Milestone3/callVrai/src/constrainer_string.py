from llm_sdk import Small_LLM_Model

from src.constrainer_func import add_fixed_text

MAX_STRING_TOKENS = 150
_JSON_ESCAPES = '"\\/bfnrt'


def scan_token(
    pending_escape: bool,
    token_text: str,
) -> tuple[str, bool, bool] | None:
    """Check a token against the JSON string grammar.

    Args:
        pending_escape: ``True`` if the previous character was a backslash.
        token_text: Candidate token text (byte-level BPE, ``Ġ`` = space).

    Returns:
        ``None`` if the token would break the JSON string. Otherwise a tuple
        ``(consumed, closed, pending_escape)``: the text kept in the string
        (up to the closing quote), whether the closing quote was reached and
        the new escape state.
    """
    if not token_text or (
        token_text.startswith("<|") and token_text.endswith("|>")
    ):
        return None

    consumed = ""

    for char in token_text:
        if pending_escape:
            if char not in _JSON_ESCAPES:
                return None
            pending_escape = False
        elif char == '"':
            return consumed, True, False
        elif char == "\\":
            pending_escape = True
        elif char == "Ġ":
            char = " "
        elif ord(char) < 32 or ord(char) > 126:
            return None
        consumed += char

    return consumed, False, pending_escape


def choose_next_string_token(
    logits: list[float],
    pending_escape: bool,
    id_to_token: dict[int, str],
) -> int:
    """Choose the highest-scoring token valid inside a JSON string.

    Tokens that would make the string invalid JSON are assigned negative
    infinity and cannot be selected.

    Args:
        logits: Logits produced by the language model.
        pending_escape: ``True`` if the previous character was a backslash.
        id_to_token: Mapping from token IDs to token text.

    Returns:
        The ID of the highest-scoring valid token.

    Raises:
        ValueError: If no valid token is available.
    """
    filtered_logits = list(logits)

    for token_id in range(len(logits)):
        token_text = id_to_token.get(token_id)

        if token_text is None or scan_token(
            pending_escape, token_text
        ) is None:
            filtered_logits[token_id] = float("-inf")

    best_id = max(
        range(len(filtered_logits)),
        key=filtered_logits.__getitem__,
    )

    if filtered_logits[best_id] == float("-inf"):
        raise ValueError("No valid string token available.")

    return best_id


def generate_string_value(
    model: Small_LLM_Model,
    ids_list: list[int],
    id_to_token: dict[int, str],
) -> str:
    """Generate a JSON string value using constrained token decoding.

    The opening quote is added before token generation. Only tokens that
    keep a valid JSON string are allowed (no raw control characters, only
    valid escapes). Generation stops at the closing quote or after
    ``MAX_STRING_TOKENS`` tokens.

    Args:
        model: Language model used to generate the string.
        ids_list: Input token IDs passed to the model. Generated token IDs
            are appended to this list.
        id_to_token: Mapping from token IDs to token text.

    Returns:
        The generated string, with quotes, as valid JSON.

    Raises:
        ValueError: If no valid token can be selected.
    """
    add_fixed_text(model, ids_list, '"')
    body = ""
    pending_escape = False

    for _ in range(MAX_STRING_TOKENS):
        logits = model.get_logits_from_input_ids(ids_list)

        best_id = choose_next_string_token(
            logits,
            pending_escape,
            id_to_token,
        )

        scanned = scan_token(pending_escape, id_to_token[best_id])
        if scanned is None:
            raise ValueError("No valid string token available.")

        consumed, closed, pending_escape = scanned
        body += consumed

        if closed:
            add_fixed_text(model, ids_list, consumed + '"')
            return '"' + body + '"'

        ids_list.append(best_id)

    if pending_escape:
        body = body[:-1]

    add_fixed_text(model, ids_list, '"')
    return '"' + body + '"'
