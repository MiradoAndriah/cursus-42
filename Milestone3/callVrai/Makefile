.PHONY: install run debug clean lint lint-strict

export UV_CACHE_DIR = /goinfre/$(USER)/uv_cache
export HF_HOME = /goinfre/$(USER)/huggingface
export UV_PROJECT_ENVIRONMENT = /goinfre/$(USER)/venvs/call_me_maybe

install:
	uv sync

run:
	uv run python -m src

debug:
	uv run python -m pdb -m src

clean:
	rm -rf __pycache__ src/__pycache__ .mypy_cache llm_sdk/__pycache__ 

lint:
	uv run flake8 .
	uv run mypy . --warn-return-any --warn-unused-ignores --ignore-missing-imports --disallow-untyped-defs --check-untyped-defs

lint-strict:
	uv run flake8 .
	uv run python -m mypy . --strict
