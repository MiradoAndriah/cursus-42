from typing import Literal
from pydantic import BaseModel, ConfigDict


class ParameterFunction(BaseModel):
    """A single parameter of a callable function."""

    model_config = ConfigDict(extra="forbid")

    type: Literal["number", "string", "boolean"]


class FunctionReturn(BaseModel):
    """Return type of a callable function."""

    model_config = ConfigDict(extra="forbid")

    type: Literal["number", "string", "boolean"]


class FunctionDefinition(BaseModel):
    """Definition of a function the model can call."""

    model_config = ConfigDict(extra="forbid")

    name: str
    description: str
    parameters: dict[str, ParameterFunction]
    returns: FunctionReturn


class Prompt(BaseModel):
    """A single natural-language prompt to process."""

    model_config = ConfigDict(extra="forbid")

    prompt: str


class Result(BaseModel):
    """A single output entry: prompt + resolved function call."""

    model_config = ConfigDict(extra="forbid")

    prompt: str
    name: str
    parameters: dict[str, int | float | str | bool]
