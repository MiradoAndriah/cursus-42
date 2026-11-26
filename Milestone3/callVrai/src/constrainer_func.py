from llm_sdk import Small_LLM_Model

"""Constrained decoding helpers for building valid JSON function calls."""


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


def get_valid_next_chars(
    already_written: str,
    all_names: list[str],
) -> tuple[set[str], set[str]]:
    """Get valid next characters and names completed by the prefix.

    Args:
        already_written: Prefix already generated.
        all_names: Available function names.

    Returns:
        A tuple containing:
        - characters that can validly follow the current prefix;
        - function names for which the current prefix is complete.
    """
    valid_names = get_valid_function_names(already_written, all_names)
    valid_chars: set[str] = set()
    full_names: set[str] = set()

    for name in valid_names:
        position = len(already_written)

        if position < len(name):
            valid_chars.add(name[position])
        else:
            full_names.add(name)

    return valid_chars, full_names


def is_token_valid(
    already_written: str,
    token_text: str,
    all_names: list[str],
) -> bool:
    """Check whether a token keeps the generated text as a valid prefix.

    Args:
        already_written: Text generated so far.
        token_text: Text represented by the candidate token.
        all_names: Available function names.

    Returns:
        ``True`` if the resulting text is a prefix of at least one
        function name, otherwise ``False``.
    """
    concatenated = already_written + token_text
    remaining_names = get_valid_function_names(concatenated, all_names)
    return bool(remaining_names)


def choose_next_token(
    logits: list[float],
    already_written: str,
    all_names: list[str],
    id_to_token: dict[int, str],
) -> int:
    """Choose the highest-scoring token that keeps decoding valid.

    Args:
        logits: Logits produced by the language model.
        already_written: Text generated so far.
        all_names: Available function names.
        id_to_token: Mapping from token IDs to their text.

    Returns:
        Token ID with the highest valid logit.

    Raises:
        ValueError: If no valid token is available.
    """
    filtered_logits = list(logits)

    for token_id in range(len(logits)):
        token_text = id_to_token.get(token_id)

        if token_text is None:
            filtered_logits[token_id] = float("-inf")
            continue

        if not is_token_valid(already_written, token_text, all_names):
            filtered_logits[token_id] = float("-inf")

    best_id = max(range(len(filtered_logits)), key=filtered_logits.__getitem__)

    if filtered_logits[best_id] == float("-inf"):
        raise ValueError("No valid token available for the current prefix.")

    return best_id


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
    already_written = ""

    while True:
        logits = model.get_logits_from_input_ids(ids_list)

        best_id = choose_next_token(
            logits,
            already_written,
            all_names,
            id_to_token,
        )

        token_text = id_to_token[best_id]
        already_written += token_text
        ids_list.append(best_id)

        _, full_names = get_valid_next_chars(
            already_written,
            all_names,
        )

        if full_names:
            break

    return already_written
