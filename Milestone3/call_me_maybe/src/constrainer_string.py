from llm_sdk import Small_LLM_Model

from src.constrainer_func import add_fixed_text


def is_plausible_string_start(text: str) -> bool:
    """Check whether text can be the beginning of a JSON string.

    Args:
        text: Text generated so far.

    Returns:
        ``True`` if the text is empty or starts with a double quote,
        otherwise ``False``.
    """
    if text == "":
        return True

    return text.startswith('"')


def choose_next_string_token(
    logits: list[float],
    already_written: str,
    id_to_token: dict[int, str],
) -> int:
    """Choose the highest-scoring token valid for a string value.

    Tokens that would make the generated text invalid as a string prefix
    are assigned negative infinity and cannot be selected.

    Args:
        logits: Logits produced by the language model.
        already_written: String text generated so far.
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

        candidate = already_written + token_text

        if not is_plausible_string_start(candidate):
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

    The opening quote is added before token generation. Generation stops
    when a second double quote is produced.

    Args:
        model: Language model used to generate the string.
        ids_list: Input token IDs passed to the model. Generated token IDs
            are appended to this list.
        id_to_token: Mapping from token IDs to token text.

    Returns:
        The generated JSON string, with tokenizer whitespace markers
        converted to regular spaces.

    Raises:
        ValueError: If no valid token can be selected.
    """
    already_written = add_fixed_text(model, ids_list, '"')

    while True:
        logits = model.get_logits_from_input_ids(ids_list)

        best_id = choose_next_string_token(
            logits,
            already_written,
            id_to_token,
        )

        token_text = id_to_token[best_id]
        already_written += token_text
        ids_list.append(best_id)

        if already_written.count('"') >= 2:
            closing_quote_index = already_written.index('"', 1)
            already_written = already_written[: closing_quote_index + 1]
            break

    return already_written.replace("Ġ", " ")
