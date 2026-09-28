from llm_sdk import Small_LLM_Model

from src.constrainer_func import get_valid_function_names


def is_plausible_number_start(text: str) -> bool:
    """Check whether text can represent the beginning of a number.

    The text is considered valid if it can already be converted to a float,
    or if appending ``"0"`` makes it convertible to a float.

    Args:
        text: Text generated so far.

    Returns:
        ``True`` if the text can represent a valid or potentially valid
        number prefix, otherwise ``False``.
    """
    if text == "":
        return True

    try:
        float(text)
        return True
    except ValueError:
        pass

    try:
        float(text + "0")
        return True
    except ValueError:
        return False


def is_plausible_string_start(text: str) -> bool:
    """Check whether text can be the beginning of a JSON string.

    Args:
        text: Text generated so far.

    Returns:
        ``True`` if the text is empty or starts with a double quote.
    """
    if text == "":
        return True

    return text.startswith('"')


def is_number_token_valid(
    already_written: str,
    token_text: str,
) -> bool:
    """Check whether a token keeps a number syntactically plausible.

    Args:
        already_written: Number text generated so far.
        token_text: Candidate token text.

    Returns:
        ``True`` if the concatenated text is a plausible number prefix.
    """
    concatenated = already_written + token_text
    return is_plausible_number_start(concatenated)


def is_value_token_valid(
    already_written: str,
    token_text: str,
    param_type: str,
) -> bool:
    """Check whether a token is valid for a given parameter type.

    Args:
        already_written: Value text generated so far.
        token_text: Candidate token text.
        param_type: Expected parameter type. Supported values are
            ``"number"``, ``"string"``, and ``"boolean"``.

    Returns:
        ``True`` if the candidate token keeps the value syntactically valid.

    Raises:
        ValueError: If ``param_type`` is not supported.
    """
    if param_type == "number":
        return is_number_token_valid(already_written, token_text)

    if param_type == "string":
        concatenated = already_written + token_text
        return is_plausible_string_start(concatenated)

    if param_type == "boolean":
        concatenated = already_written + token_text
        possibilities = get_valid_function_names(
            concatenated,
            ["true", "false"],
        )
        return len(possibilities) > 0

    raise ValueError(f"Unknown param_type: {param_type}")


def choose_next_number_token(
    logits: list[float],
    already_written: str,
    id_to_token: dict[int, str],
) -> int:
    """Choose the highest-scoring token valid for a number.

    Args:
        logits: Logits produced by the language model.
        already_written: Number text generated so far.
        id_to_token: Mapping from token IDs to token text.

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

        if not is_number_token_valid(already_written, token_text):
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
    """Generate a number value using constrained token decoding.

    Generation stops when the generated number reaches the maximum length,
    when the model's unconstrained best token starts a JSON separator, or
    when no valid number token can be generated.

    Args:
        model: Language model used to generate the value.
        ids_list: Input token IDs passed to the model. The generated token
            IDs are appended to this list.
        id_to_token: Mapping from token IDs to token text.

    Returns:
        The generated number as a string.
    """
    already_written = ""
    limit = 10

    while len(already_written) < limit:
        logits = model.get_logits_from_input_ids(ids_list)

        raw_best_id = max(
            range(len(logits)),
            key=logits.__getitem__,
        )
        raw_best_text = id_to_token.get(raw_best_id, "")

        if already_written and (
            raw_best_text.startswith(",") or raw_best_text.startswith("}")
        ):
            break

        best_id = choose_next_number_token(
            logits,
            already_written,
            id_to_token,
        )

        token_text = id_to_token[best_id]

        if not is_number_token_valid(already_written, token_text):
            break

        already_written += token_text
        ids_list.append(best_id)

    return already_written
