#!/usr/bin/env python3
from abc import ABC, abstractmethod
from typing import Any

class DataProcessor(ABC):
    def __init__(self):
        self.file = []
        self.compteur = 0
    
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
    def __init__(self):
        super().__init__()
    
    def validate(self, data: Any) -> bool:
        if isinstance(data, int) or isinstance(data, float):
            return True
        
        if isinstance(data, list):
            for element in data:
                if not isinstance(element, int) and not isinstance(element, float):
                    return False
            return True
        else:
            return False
    
    def ingest(self, data: int | float | list) -> None:
        if not self.validate(data):
            raise Exception("Improper log data")
        if not isinstance(data, list):
            data = [data]
        for element in data:
            element = str(element)
            self.file += [(self.compteur, element)]
            self.compteur += 1


class TextProcessor(DataProcessor):
    def __init__(self):
        super().__init__()

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
    
    def ingest(self, data: str | list) -> None:
        if not self.validate(data):
            raise Exception("Improper text data")
        if not isinstance(data, list):
            data = [data]
        for element in data:
            self.file += [(self.compteur, element)]
            self.compteur += 1


class LogProcessor(DataProcessor):
    def __init__(self):
        super().__init__()

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

    def ingest(self, data: dict | list) -> Any:
        if not self.validate(data):
            raise Exception("Improper log data")
        if not isinstance(data, list):
            data = [data]
        for element in data:
            values = list(element.values())
            format_string = values[0] + ":" + values[1]
            self.file += [(self.compteur, format_string)]
            self.compteur += 1