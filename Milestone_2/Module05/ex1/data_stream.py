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


class DataStream:
    def __init__(self) -> None:
        self.data_process: list[DataProcessor] = []

    def register_processor(self, proc: DataProcessor) -> None:
        self.data_process += [proc]

    def process_stream(self, stream: list[Any]) -> None:
        for element in stream:
            treat = False
            for proc in self.data_process:
                if proc.validate(element):
                    proc.ingest(element)
                    treat = True
                    break

            if not treat:
                print("DataStream error - "
                      f"Can't process element in stream: {element}"
                      )

    def print_processors_stats(self) -> None:
        print("== DataStream statistics ==")
        if not self.data_process:
            print("No processor found, no data")
        for proc in self.data_process:
            name = proc.__class__.__name__.replace("Processor", " Processor")
            print(
                f"{name}: total {proc.rank} items processed, remaining "
                f"{len(proc.file)} on processor"
                )


if __name__ == "__main__":
    print("=== Code Nexus - Data Stream ===\n")
    print("Initialize Data Stream...")
    stream = DataStream()
    stream.print_processors_stats()
    print()
    num_data = NumericProcessor()
    text_data = TextProcessor()
    log_data = LogProcessor()
    print("\nRegistering Numeric Processor\n")
    stream.register_processor(num_data)
    data = [
        'Hello world',
        [3.14, -1, 2.71],
        [{
            'log_level': 'WARNING',
            'log_message': 'Telnet access! Use ssh instead'
        },
         {
            'log_level': 'INFO',
            'log_message': 'User wil isconnected'
            }], 42, ['Hi', 'five']
         ]
    print(f"Send first batch of data on stream: {data}")
    stream.process_stream(data)
    stream.print_processors_stats()
    print()
    print("Registering other data processors")
    print("Send the same batch again")
    stream.register_processor(text_data)
    stream.register_processor(log_data)
    stream.process_stream(data)
    stream.print_processors_stats()
    print()
    for i in range(3):
        num_data.output()
    for i in range(2):
        text_data.output()
    for i in range(1):
        log_data.output()
    print(f"Consume some elements from the data processors: "
          f"Numeric {len(num_data.file)}, Text "
          f"{len(text_data.file)}, Log {len(log_data.file)}")

    stream.print_processors_stats()
