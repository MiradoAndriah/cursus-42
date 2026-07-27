#!/usr/bin/env python3
from abc import ABC, abstractmethod
from typing import Any, Protocol


class DataProcessor(ABC):
    def __init__(self) -> None:
        self.data_file: list[tuple[int, str]] = []
        self.rank = 0

    @abstractmethod
    def validate(self, data: Any) -> bool:
        pass

    @abstractmethod
    def ingest(self, data: Any) -> None:
        pass

    def output(self, nb: int) -> list[tuple[int, str]]:
        result = []
        for i in range(nb):
            if not self.data_file:
                break
            element = self.data_file[0]
            self.data_file.pop(0)
            result += [element]
        return result


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

    def ingest(self, data: int | float | list[int] | list[float]) -> None:
        if not self.validate(data):
            raise TypeError("Improper numeric data")
        if not isinstance(data, list):
            data = [data]
        for element in data:
            element_str = str(element)
            self.data_file += [(self.rank, element_str)]
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
            self.data_file += [(self.rank, element)]
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
            self.data_file += [(self.rank, format_string)]
            self.rank += 1


class ExportPlugin(Protocol):
    def process_output(self, data: list[tuple[int, str]]) -> None:
        pass


class CSVExportPlugin:
    def process_output(self, data: list[tuple[int, str]]) -> None:
        values = []
        for value in data:
            values.append(value[1])
        join = ",".join(values)
        print(f"CSV Output:\n{join}")


class JSONExportPlugin:
    def process_output(self, data: list[tuple[int, str]]) -> None:
        pairs = []
        for value in data:
            key: str = f"item_{value[0]}"
            pair = f'"{key}": "{value[1]}"'
            pairs.append(pair)
        json_line = "{" + ", ".join(pairs) + "}"
        print(f"JSON Output:\n{json_line}")


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
                f"{len(proc.data_file)} on processor"
                )

    def output_pipeline(self, nb: int, plugin: ExportPlugin) -> None:
        for proc in self.data_process:
            data = proc.output(nb)
            if data:
                plugin.process_output(data)


if __name__ == "__main__":
    print("=== Code Nexus - Data Pipeline ===")
    print("\nInitialize Data Stream...\n")
    stream = DataStream()
    stream.print_processors_stats()
    print()
    num_data = NumericProcessor()
    text_data = TextProcessor()
    log_data = LogProcessor()
    print("\nRegistering Processors\n")
    stream.register_processor(num_data)
    stream.register_processor(text_data)
    stream.register_processor(log_data)

    data = [
        'Hello world',
        [3.14, -1, 2.71],
        [
            {
                'log_level': 'WARNING',
                'log_message': 'Telnet access! Use ssh instead'
            },
            {
                'log_level': 'INFO',
                'log_message': 'User wil isconnected'
            }
        ], 42, ['Hi', 'five']
        ]
    print(f"Send first batch of data on stream: {data}\n")
    stream.process_stream(data)
    stream.print_processors_stats()
    print()
    csv = CSVExportPlugin()
    print("Send 3 processed data from each processor to a CSV plugin:")
    stream.output_pipeline(3, csv)
    print()
    stream.print_processors_stats()
    print()
    data2 = [
        21,
        [
            "I love AI",
            "LLMs are wonderful",
            "Stay healthy"
        ],
        [
            {
                "log_level": "ERROR",
                "log_message": "500 server crash"
            },
            {
                "log_level": "NOTICE",
                "log_message": "Certificate expires in 10 days"
            }
        ],
        [32, 42, 64, 84, 128, 168],
        "World hello"
    ]
    print(f"Send another batch of data: {data2}\n")
    stream.process_stream(data2)
    stream.print_processors_stats()
    print()
    print("Send 5 processed data from each processor to a JSON plugin:")
    json = JSONExportPlugin()
    stream.output_pipeline(5, json)
    print()
    stream.print_processors_stats()
