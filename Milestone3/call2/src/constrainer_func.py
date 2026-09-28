from llm_sdk import Small_LLM_Model


def add_fixed_text(
    model: Small_LLM_Model,
    ids_list: list[int],
    text: str,
) -> str:
    """Encode fixed text, append its token IDs to ``ids_list``, and return it.

    Args:
        model: Language model used to encode the text.
        ids_list: List of token IDs to extend.
        text: Text to encode and append.

    Returns:
        The original ``text`` value.
    """
    new_ids: list[int] = model.encode(text)[0].tolist()
    ids_list.extend(new_ids)
    return text


def get_valid_function_names(
    already_written: str,
    all_names: list[str],
) -> list[str]:
    """Return function names matching the current written prefix.

    Args:
        already_written: Prefix already generated.
        all_names: Available function names.

    Returns:
        Function names that start with ``already_written``.
    """
    return [name for name in all_names if name.startswith(already_written)]


def get_fullname_func(
    model: Small_LLM_Model,
    ids_list: list[int],
    all_names: list[str],
    id_to_token: dict[int, str],
) -> str:
    """Generate a complete function name using constrained decoding.

    Args:
        model: Language model used to generate the function name.
        ids_list: Input token IDs passed to the model.
        all_names: Available function names.
        id_to_token: Mapping from token IDs to their text.

    Returns:
        A function name from ``all_names`` generated token by token.

    Raises:
        ValueError: If no valid token can be selected.
    """
    written = ""

    while not any(written == name for name in all_names):
        logits = model.get_logits_from_input_ids(ids_list)

        best_id, best_score = None, float("-inf")
        for token_id, score in enumerate(logits):
            token_text = id_to_token.get(token_id)
            if token_text is None:
                continue
            candidate = written + token_text
            if any(name.startswith(candidate) for name in all_names) and score > best_score:
                best_id, best_score = token_id, score

        if best_id is None:
            raise ValueError("No valid token available for the current prefix.")

        written += id_to_token[best_id]
        ids_list.append(best_id)

    return written
