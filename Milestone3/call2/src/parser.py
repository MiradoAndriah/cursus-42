import json
from typing import Any, cast

from pydantic import ValidationError

from src.models import FunctionDefinition, Prompt

JsonObject = dict[str, Any]
JsonData = list[JsonObject] | JsonObject


def opening_file(file: str) -> JsonData:
    """Open a JSON file and return its decoded content.

    Args:
        file: Path to the JSON file.

    Returns:
        The decoded JSON data as a list of objects or a single object.

    Raises:
        ValueError: If the file does not exist or contains invalid JSON.
    """
    try:
        with open(file, encoding="utf-8") as json_file:
            data: Any = json.load(json_file)

    except FileNotFoundError as error:
        raise ValueError(f"File not found: {file}") from error

    except json.JSONDecodeError as error:
        raise ValueError(f"Invalid JSON in file: {file}") from error

    return cast(JsonData, data)


def parser_json(file: str) -> list[FunctionDefinition]:
    """Parse function definitions from a JSON file.

    The JSON file must contain a list of objects compatible with the
    ``FunctionDefinition`` Pydantic model.

    Args:
        file: Path to the JSON file.

    Returns:
        A list of validated function definitions.

    Raises:
        ValueError: If the JSON structure is invalid or a function
            definition cannot be validated.
    """
    data = opening_file(file)

    if not isinstance(data, list):
        raise ValueError(f"Expected a list of function definitions in: {file}")

    result: list[FunctionDefinition] = []

    for element in data:
        try:
            func_def = FunctionDefinition(**element)
            result.append(func_def)
        except ValidationError as error:
            raise ValueError(f"Invalid function definition: {error}") from error

    return result


def parser_prompts(file: str) -> list[Prompt]:
    """Parse prompts from a JSON file.

    The JSON file must contain a list of objects compatible with the
    ``Prompt`` Pydantic model.

    Args:
        file: Path to the JSON file.

    Returns:
        A list of validated prompts.

    Raises:
        ValueError: If the JSON structure is invalid or a prompt
            cannot be validated.
    """
    data = opening_file(file)

    if not isinstance(data, list):
        raise ValueError(f"Expected a list of prompts in: {file}")

    result: list[Prompt] = []

    for element in data:
        try:
            prompt = Prompt(**element)
            result.append(prompt)
        except ValidationError as error:
            raise ValueError(f"Invalid prompt: {error}") from error

    return result
