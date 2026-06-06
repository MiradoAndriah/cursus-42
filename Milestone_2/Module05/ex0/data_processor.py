#!/usr/bin/env python3
from abc import ABC, abstractmethod
from typing import Any

class DataProcessor(ABC):
    def __init__(self):
        self.file = []
        self.compteur = 0
    
    @abstractmethod
    def validate(self):
        pass

    @abstractmethod
    def ingest(self):
        pass

    def output(self):
        first_element = self.file[0]
        self.file.pop(0)
        return first_element


class NumericProcessor(DataProcessor):
    def __init__(self):
        super().__init__()
    
    def validate(self, data: Any) -> bool:
        if isinstance(data, int) or issubclass(data, float):
            return True
        
        if isinstance(data, list):
            for element in data:
                if not isinstance(element, int) and not isinstance(element, float):
                    return False
            return True
        else:
            return False
    
    def ingest(self, data: Any):
        if not self.validate(data):
            raise("Improper log data")
        if not isinstance(data, list):
            data = [data]