from llm_sdk import Small_LLM_Model

from src.constrainer_func import add_fixed_text


def is_plausible_string_start(text: str) -> bool:
    """Check whether text can be the beginning of a JSON string.

    Args:
        text: Text generated so far.

    Returns:
        True if the text is empty or starts with a double quote,
        otherwise False.
    """
    return text == "" or text.startswith('"')


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
    written = add_fixed_text(model, ids_list, '"')

    while written.count('"') < 2:
        logits = model.get_logits_from_input_ids(ids_list)

        # Pick the highest-scoring token that keeps the string valid
        best_id, best_score = None, float("-inf")
        for token_id, score in enumerate(logits):
            token_text = id_to_token.get(token_id)
            if token_text is None:
                continue
            if is_plausible_string_start(written + token_text) and score > best_score:
                best_id, best_score = token_id, score

        if best_id is None:
            raise ValueError("No valid string token available.")

        written += id_to_token[best_id]
        ids_list.append(best_id)

    closing_quote_index = written.index('"', 1)
    written = written[: closing_quote_index + 1]

    return written.replace("Ġ", " ")
