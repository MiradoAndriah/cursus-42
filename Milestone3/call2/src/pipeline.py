import json
import os
from typing import Any

from llm_sdk import Small_LLM_Model

from src import Result, parser_json, parser_prompts
from src.generator import generate_function_call


def process_all_prompts(
    functions_path: str,
    tests_path: str,
    output_path: str,
) -> None:
    """Generate function calls for all prompts and save the results.

    The function loads the function definitions and test prompts, builds
    the model input for each prompt, generates a constrained JSON function
    call, validates the generated result, and writes all results to a JSON
    output file.

    Args:
        functions_path: Path to the function definitions JSON file.
        tests_path: Path to the prompts JSON file.
        output_path: Path where the generated results are written.

    Raises:
        ValueError: If a generated function call does not contain the
            expected JSON fields.
        OSError: If an input or output file cannot be accessed.
        json.JSONDecodeError: If a vocabulary or tokenizer file contains
            invalid JSON.
    """
    model = Small_LLM_Model()

    vocab_path = model.get_path_to_vocab_file()

    with open(vocab_path, encoding="utf-8") as vocab_file:
        vocab_data: dict[str, int] = json.load(vocab_file)

    id_to_token: dict[int, str] = {
        token_id: token
        for token, token_id in vocab_data.items()
    }

    tokenizer_path = model.get_path_to_tokenizer_file()

    with open(tokenizer_path, encoding="utf-8") as tokenizer_file:
        tokenizer_data: dict[str, Any] = json.load(tokenizer_file)

    added_tokens = tokenizer_data.get("added_tokens", [])

    if not isinstance(added_tokens, list):
        raise ValueError("Invalid tokenizer data: 'added_tokens' must be a list")

    for token_data in added_tokens:
        if not isinstance(token_data, dict):
            raise ValueError(
                "Invalid tokenizer data: an added token must be an object"
            )

        token_id = token_data.get("id")
        token_content = token_data.get("content")

        if not isinstance(token_id, int):
            raise ValueError(
                "Invalid tokenizer data: token ID must be an integer"
            )

        if not isinstance(token_content, str):
            raise ValueError(
                "Invalid tokenizer data: token content must be a string"
            )

        id_to_token[token_id] = token_content

    all_functions = parser_json(functions_path)
    all_prompts = parser_prompts(tests_path)

    results: list[Result] = []

    for prompt_entry in all_prompts:
        question = prompt_entry.prompt

        functions_json = json.dumps(
            [function.model_dump() for function in all_functions]
        )

        complete_text = (
            f"Available functions: {functions_json}\n\n"
            f"Question: {question}\n"
            'Answer with a JSON object: {"name": "'
        )

        ids_tensor = model.encode(complete_text)
        ids_list: list[int] = ids_tensor[0].tolist()

        generated = generate_function_call(
            model,
            ids_list,
            all_functions,
            id_to_token,
        )

        parsed: Any = json.loads(generated)

        if not isinstance(parsed, dict):
            raise ValueError(
                f"Generated function call is not a JSON object: {generated}"
            )

        name = parsed.get("name")
        parameters = parsed.get("parameters")

        if not isinstance(name, str):
            raise ValueError(
                f"Generated function call has an invalid name: {generated}"
            )

        if not isinstance(parameters, dict):
            raise ValueError(
                "Generated function call has invalid parameters: "
                f"{generated}"
            )

        result = Result(
            prompt=question,
            name=name,
            parameters=parameters,
        )

        results.append(result)

    output_data = [result.model_dump() for result in results]
    output_text = json.dumps(
        output_data,
        indent=2,
        ensure_ascii=False,
    )

    output_directory = os.path.dirname(output_path)

    if output_directory:
        os.makedirs(output_directory, exist_ok=True)

    with open(output_path, "w", encoding="utf-8") as output_file:
        output_file.write(output_text)
