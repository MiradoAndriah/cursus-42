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

    def ingest(self, data: Any) -> None:
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
            format_string = values[0] + ": " + values[1]
            self.file += [(self.rank, format_string)]
            self.rank += 1


if __name__ == "__main__":
    print("=== Code Nexus - Data Processor ===\n")
    print("Testing Numeric Processor...")
    numericProcessor = NumericProcessor()
    data1 = 42
    print(
        f" Trying to validate input '{data1}': "
        f"{numericProcessor.validate(data1)}"
        )
    data2 = "Hello"
    print(
        f" Trying to validate input '{data2}': "
        f"{numericProcessor.validate(data2)}"
        )
    data3 = "foo"
    try:
        numericProcessor.ingest(data3)
    except Exception as e:
        print(
            f" Test invalid ingestion of string "
            f"{data3!r} without prior validation:"
            )
        print(f" Got exception: {e}")

    data4 = [1, 2, 3, 4, 5]
    print(f" Processing data: {data4}")
    try:
        numericProcessor.ingest(data4)
        print(" Extracting 3 values...")
        for i in range(3):
            rank, data = numericProcessor.output()
            print(f" Numeric value {rank}: {data}")
    except Exception as e:
        print(f" Got exception: {e}")
    print()

    print("Testing Text Processor...")
    textProcessor = TextProcessor()
    print(f" Trying to validate input '{data1}': "
          f"{textProcessor.validate(data1)}"
          )
    data_text = ['Hello', 'Nexus', 'World']
    print(f" Processing data: {data_text}")
    try:
        textProcessor.ingest(data_text)
        print(" Extracting 1 value...")
        for i in range(1):
            rank, data = textProcessor.output()
            print(f" Text value {rank}: {data}")
    except Exception as e:
        print(f" Got exception: {e}")
    print()

    print("Testing Log Processor...")
    logProcessor = LogProcessor()
    print(f" Trying to validate input '{data2}': "
          f"{logProcessor.validate(data2)}"
          )
    data_log = [
        {'log_level': 'NOTICE', 'log_message': 'Connection to server'},
        {'log_level': 'ERROR', 'log_message': 'Unauthorized access!!'}
        ]
    print(f" Processing data: {data_log}")
    try:
        logProcessor.ingest(data_log)
        print(" Extracting 2 values...")
        for i in range(2):
            rank, data = logProcessor.output()
            print(f" Log entry {rank}: {data}")
    except Exception as e:
        print(f" Got exception: {e}")
