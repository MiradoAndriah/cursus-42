import re

from llm_sdk import Small_LLM_Model

# Valid prefix of a JSON number (can still be completed into a valid one).
_NUMBER_PREFIX = re.compile(
    r"^(-|-?(0|[1-9][0-9]*)"
    r"(\.([0-9]+([eE][+-]?[0-9]*)?)?|[eE][+-]?[0-9]*)?)?$"
)
# Complete JSON number.
_NUMBER_FULL = re.compile(r"^-?(0|[1-9][0-9]*)(\.[0-9]+)?([eE][+-]?[0-9]+)?$")


def is_number_token_valid(
    already_written: str,
    token_text: str,
    space_allowed: bool = False,
) -> bool:
    """Check whether a token keeps a valid JSON number prefix.

    Args:
        already_written: Number text generated so far.
        token_text: Candidate token text.
        space_allowed: If ``True``, the token may start with the space
            marker ``Ġ`` (the tokenizer merges the space with ``-``).

    Returns:
        ``True`` if the concatenated text can still become a JSON number.
    """
    if space_allowed and token_text.startswith("Ġ"):
        token_text = token_text[1:]
        if not token_text:
            return True

    if not token_text:
        return False

    return bool(_NUMBER_PREFIX.match(already_written + token_text))


def trim_to_complete_number(text: str) -> str:
    """Remove trailing characters until the text is a complete JSON number.

    Args:
        text: Number text that may be incomplete (e.g. ``"1.5e"``).

    Returns:
        The longest complete JSON number prefix, or ``"0"`` if none.
    """
    while text and not _NUMBER_FULL.match(text):
        text = text[:-1]

    return text or "0"


def choose_next_number_token(
    logits: list[float],
    already_written: str,
    id_to_token: dict[int, str],
    space_allowed: bool = False,
) -> int:
    """Choose the highest-scoring token valid for a number.

    Args:
        logits: Logits produced by the language model.
        already_written: Number text generated so far.
        id_to_token: Mapping from token IDs to token text.
        space_allowed: Whether a leading ``Ġ`` is accepted.

    Returns:
        The ID of the highest-scoring valid token.

    Raises:
        ValueError: If no valid token is available.
    """
    filtered_logits = list(logits)

    for token_id in range(len(logits)):
        token_text = id_to_token.get(token_id)

        if token_text is None:
            filtered_logits[token_id] = float("-inf")
            continue

        if not is_number_token_valid(
            already_written, token_text, space_allowed
        ):
            filtered_logits[token_id] = float("-inf")

    best_id = max(
        range(len(filtered_logits)),
        key=filtered_logits.__getitem__,
    )

    if filtered_logits[best_id] == float("-inf"):
        raise ValueError("No valid number token available.")

    return best_id


def generate_number_value(
    model: Small_LLM_Model,
    ids_list: list[int],
    id_to_token: dict[int, str],
) -> str:
    """Generate a JSON number using constrained token decoding.

    Generation stops when the number is complete and the model's best
    unconstrained token cannot continue it (e.g. ``,`` or ``}``), or when
    the maximum length is reached.

    Args:
        model: Language model used to generate the value.
        ids_list: Input token IDs passed to the model. The generated token
            IDs are appended to this list.
        id_to_token: Mapping from token IDs to token text.

    Returns:
        The generated number as a valid JSON number string.
    """
    already_written = ""
    limit = 10
    space_allowed = True

    while len(already_written) < limit:
        logits = model.get_logits_from_input_ids(ids_list)

        raw_best_id = max(
            range(len(logits)),
            key=logits.__getitem__,
        )
        raw_best_text = id_to_token.get(raw_best_id, "")

        if _NUMBER_FULL.match(already_written) and not is_number_token_valid(
            already_written, raw_best_text
        ):
            break

        best_id = choose_next_number_token(
            logits,
            already_written,
            id_to_token,
            space_allowed,
        )

        token_text = id_to_token[best_id]
        if space_allowed and token_text.startswith("Ġ"):
            token_text = token_text[1:]
        space_allowed = False

        already_written += token_text
        ids_list.append(best_id)

    return trim_to_complete_number(already_written)
