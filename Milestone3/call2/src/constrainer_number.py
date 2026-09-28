from llm_sdk import Small_LLM_Model

from src.constrainer_func import get_valid_function_names


def is_plausible_number_start(text: str) -> bool:
    """Check whether text can represent the beginning of a number.

    The text is considered valid if it can already be converted to a float,
    or if appending "0" makes it convertible to a float.

    Args:
        text: Text generated so far.

    Returns:
        True if the text can represent a valid or potentially valid
        number prefix, otherwise False.
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
        True if the text is empty or starts with a double quote.
    """
    return text == "" or text.startswith('"')


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
            "number", "string", and "boolean".

    Returns:
        True if the candidate token keeps the value syntactically valid.

    Raises:
        ValueError: If param_type is not supported.
    """
    concatenated = already_written + token_text

    if param_type == "number":
        return is_plausible_number_start(concatenated)

    if param_type == "string":
        return is_plausible_string_start(concatenated)

    if param_type == "boolean":
        return len(get_valid_function_names(concatenated, ["true", "false"])) > 0

    raise ValueError(f"Unknown param_type: {param_type}")


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
    written = ""
    limit = 10

    while len(written) < limit:
        logits = model.get_logits_from_input_ids(ids_list)

        # Stop early if the model's unconstrained choice ends the number
        raw_best_id = max(range(len(logits)), key=logits.__getitem__)
        raw_best_text = id_to_token.get(raw_best_id, "")
        if written and raw_best_text.startswith((",", "}")):
            break

        # Pick the highest-scoring token that keeps the number valid
        best_id, best_score = None, float("-inf")
        for token_id, score in enumerate(logits):
            token_text = id_to_token.get(token_id)
            if token_text is None:
                continue
            if is_plausible_number_start(written + token_text) and score > best_score:
                best_id, best_score = token_id, score

        if best_id is None:
            break

        written += id_to_token[best_id]
        ids_list.append(best_id)

    return written
