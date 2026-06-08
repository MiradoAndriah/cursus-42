#!/usr/bin/env python3
from abc import ABC, abstractmethod
from typing import Any


class DataProcessor(ABC):
    def __init__(self) -> None:
        self.file: list[tuple[int, str]] = []
        self.rank = 0

    @abstractmethod
    def validate(self, data: Any) -> bool:
        pass

    @abstractmethod
    def ingest(self, data: Any) -> None:
        pass

    def output(self) -> tuple[int, str]:
        first_element = self.file[0]
        self.file.pop(0)
        return first_element


class NumericProcessor(DataProcessor):
    def validate(self, data: Any) -> bool:
        if isinstance(data, int) or isinstance(data, float):
            return True

        if isinstance(data, list):
            for element in data:
                if not isinstance(element, (int, float)):
                    return False
            return True
        else:
            return False

    def ingest(self, data: int | float | list[int | float]) -> None:
        if not self.validate(data):
            raise TypeError("Improper numeric data")
        if not isinstance(data, list):
            data = [data]   
        for element in data:
            element_str = str(element)
            self.file += [(self.rank, element_str)]
            self.rank += 1


class TextProcessor(DataProcessor):
    def validate(self, data: Any) -> bool:
        if isinstance(data, str):
            return True

        if isinstance(data, list):
            for element in data:
                if not isinstance(element, str):
                    return False
            return True
        else:
            return False

    def ingest(self, data: str | list[str]) -> None:
        if not self.validate(data):
            raise TypeError("Improper text data")
        if not isinstance(data, list):
            data = [data]
        for element in data:
            self.file += [(self.rank, element)]
            self.rank += 1


class LogProcessor(DataProcessor):
    def validate(self, data: Any) -> bool:
        if isinstance(data, dict):
            for key, value in data.items():
                if not isinstance(key, str) or not isinstance(value, str):
                    return False
            return True

        if isinstance(data, list):
            for element in data:
                if not isinstance(element, dict):
                    return False
            return True
        else:
            return False

    def ingest(self, data: dict[str, str] | list[dict[str, str]]) -> None:
        if not self.validate(data):
            raise TypeError("Improper log data")
        if not isinstance(data, list):
            data = [data]
        for element in data:
            values = list(element.values())
            format_string = values[0] + ":" + values[1]
            self.file += [(self.rank, format_string)]
            self.rank += 1


if __name__ == "__main__":
    print("=== Code Nexus - Data Processor ===\n")
    print("Testing Numeric Processor...")
    numericProcessor = NumericProcessor()
    data1 = 42
    print(f"Trying to validate input '{data1}': {numericProcessor.validate(data1)}")
    data2 = "Hello"
    print(f"Trying to validate input '{data2}': {numericProcessor.validate(data2)}")
    data3 = "foo"
    try:
        numericProcessor.ingest(data3)
    except Exception as e:
        print(f"Test invalid ingestion of string {data3!r} without prior validation:")
        print(f"Got exception: {e}")