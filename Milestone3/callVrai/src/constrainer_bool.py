"""Constrained generation of JSON boolean values (true/false)."""

from src.constrainer_func import get_fullname_func
from llm_sdk import Small_LLM_Model


def generate_bool_value(
    model: Small_LLM_Model, ids_list: list[int], id_to_token: dict[int, str]
) -> str:
    """Generate a JSON boolean literal using constrained decoding.

    Reuses get_fullname_func with a fixed list of the only two valid
    boolean literals, so the model is constrained to pick exactly
    "true" or "false".

    Args:
        model: The loaded language model used for token generation.
        ids_list: The current token id sequence (prompt + tokens
            generated so far). Mutated in place as new tokens are
            appended during generation.
        id_to_token: Mapping from token id to its decoded text,
            covering the full model vocabulary.

    Returns:
        The generated literal, either "true" or "false".
    """
    result = get_fullname_func(model, ids_list, ["true", "false"], id_to_token)
    return result
