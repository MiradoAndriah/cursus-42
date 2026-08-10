try:
    from pydantic import BaseModel, Field, ValidationError
except ImportError:
    raise SystemExit(
        "You must use which Pydantic 2.x\n"
        "  Use: 'pip install pydantic >= 2'"
    )
from datetime import datetime
from typing import Optional


class SpaceStation(BaseModel):
    station_id: str = Field(min_length=3, max_length=10)
    name: str = Field(min_length=1, max_length=50)
    crew_size: int = Field(ge=1, le=20)
    power_level: float = Field(ge=0.0, le=100.0)
    oxygen_level: float = Field(ge=0.0, le=100.0)
    last_maintenance: datetime
    is_operational: bool = True
    notes: Optional[str] = Field(default=None, max_length=200)


def main() -> None:
    try:
        valid_space = SpaceStation(
            station_id="ISS001",
            name="International Space Station",
            crew_size=6,
            power_level=85.5,
            oxygen_level=92.3,
            last_maintenance=datetime.now()
            )

        print("Space Station Data Validation")
        print("========================================")
        print("Valid station created:")
        print(f"ID: {valid_space.station_id}")
        print(f"Name: {valid_space.name}")
        print(f"Crew: {valid_space.crew_size} people")
        print(f"Power: {valid_space.power_level}%")
        print(f"Oxygen: {valid_space.oxygen_level}%")
        print(f"Status: {valid_space.is_operational}")

    except ValidationError as e:
        print("\n========================================")
        print("Expected validation error:")
        for i in e.errors():
            print(i["msg"])

    try:
        valid_space = SpaceStation(
            station_id="ISS001",
            name="International Space Station",
            crew_size=21,
            power_level=85.5,
            oxygen_level=92.3,
            last_maintenance=datetime.now()
            )

    except ValidationError as e:
        print("\n========================================")
        print("Expected validation error:")
        for i in e.errors():
            print(i["msg"])


if __name__ == "__main__":
    main()
