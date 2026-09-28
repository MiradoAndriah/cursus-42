from llm_sdk import Small_LLM_Model

from src import (
    FunctionDefinition,
    add_fixed_text,
    generate_bool_value,
    generate_number_value,
    generate_string_value,
    get_fullname_func,
)


def find_function_definition(
    chosen_name: str,
    functions: list[FunctionDefinition],
) -> FunctionDefinition:
    """Find a function definition by its name.

    Args:
        chosen_name: Name of the function to find.
        functions: Available function definitions.

    Returns:
        The function definition matching ``chosen_name``.

    Raises:
        ValueError: If no function has the requested name.
    """
    for func in functions:
        if func.name == chosen_name:
            return func

    raise ValueError(f"Function {chosen_name!r} is not found")


def generate_function_call(
    model: Small_LLM_Model,
    ids_list: list[int],
    all_functions: list[FunctionDefinition],
    id_to_token: dict[int, str],
) -> str:
    """Generate a constrained JSON function call.

    The function name is selected from the available function definitions.
    Each parameter value is then generated according to its declared type.

    Args:
        model: Language model used to generate the function call.
        ids_list: Input token IDs passed to the model. Generated token IDs
            are appended to this list.
        all_functions: Available function definitions.
        id_to_token: Mapping from token IDs to token text.

    Returns:
        A JSON-formatted function call containing the selected function name
        and its generated parameters.

    Raises:
        ValueError: If no matching function is found or a parameter has an
            unsupported type.
    """
    all_names = [func.name for func in all_functions]

    chosen_name = get_fullname_func(
        model,
        ids_list,
        all_names,
        id_to_token,
    )

    func_def = find_function_definition(
        chosen_name,
        all_functions,
    )

    result = (
        '{"name": "'
        + chosen_name
        + '"'
        + add_fixed_text(
            model,
            ids_list,
            ', "parameters": {',
        )
    )

    parameter_names = list(func_def.parameters.keys())

    for index, parameter_name in enumerate(parameter_names):
        add_fixed_text(
            model,
            ids_list,
            f'"{parameter_name}": ',
        )

        parameter_type = func_def.parameters[parameter_name].type

        if parameter_type == "number":
            value = generate_number_value(
                model,
                ids_list,
                id_to_token,
            )
        elif parameter_type == "string":
            value = generate_string_value(
                model,
                ids_list,
                id_to_token,
            )
        elif parameter_type == "boolean":
            value = generate_bool_value(
                model,
                ids_list,
                id_to_token,
            )
        else:
            raise ValueError(f"Unsupported parameter type: {parameter_type!r}")

        result += f'"{parameter_name}": {value}'

        if index < len(parameter_names) - 1:
            add_fixed_text(
                model,
                ids_list,
                ", ",
            )
            result += ", "

    result += add_fixed_text(
        model,
        ids_list,
        "}}",
    )

    return result
