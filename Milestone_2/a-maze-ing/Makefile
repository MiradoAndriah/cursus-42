PYTHON    = python3
MAIN      = a_maze_ing.py
CONFIG    = config.txt
PKG_DIR   = mazegen_pkg

.PHONY: install run debug lint lint-strict clean build-pkg

install:
	pip install flake8 mypy --break-system-packages

run:
	$(PYTHON) $(MAIN) $(CONFIG)

debug:
	$(PYTHON) -m pdb $(MAIN) $(CONFIG)

lint:
	flake8 .
	mypy . \
	  --warn-return-any \
	  --warn-unused-ignores \
	  --ignore-missing-imports \
	  --disallow-untyped-defs \
	  --check-untyped-defs

lint-strict:
	flake8 .
	mypy . --strict

clean:
	find . -type d -name "__pycache__" -exec rm -rf {} + 2>/dev/null || true
	find . -type d -name ".mypy_cache"  -exec rm -rf {} + 2>/dev/null || true
	find . -type d -name "*.egg-info"   -exec rm -rf {} + 2>/dev/null || true
	find . -type d -name "dist"         -exec rm -rf {} + 2>/dev/null || true
	find . -type d -name "build"        -exec rm -rf {} + 2>/dev/null || true

build-pkg:
	cd $(PKG_DIR) && pip install build --break-system-packages && python3 -m build
