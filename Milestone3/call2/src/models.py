from typing import Literal
from pydantic import BaseModel


class ParameterFunction(BaseModel):
    """A single parameter of a callable function."""

    type: Literal["number", "string", "boolean"]


class FunctionReturn(BaseModel):
    """Return type of a callable function."""

    type: Literal["number", "string", "boolean"]


class FunctionDefinition(BaseModel):
    """Definition of a function the model can call."""

    name: str
    description: str
    parameters: dict[str, ParameterFunction]
    returns: FunctionReturn


class Prompt(BaseModel):
    """A single natural-language prompt to process."""

    prompt: str


class Result(BaseModel):
    """A single output entry: prompt + resolved function call."""

    prompt: str
    name: str
    parameters: dict[str, int | float | str | bool]
