try:
    from pydantic import BaseModel, Field, ValidationError, model_validator
except ImportError:
    raise SystemExit(
        "You must use which Pydantic 2.x\n"
        "  Use: 'pip install pydantic >= 2'"
    )
from datetime import datetime
from enum import Enum
from typing import Optional


class ContactType(Enum):
    radio = "radio"
    visual = "visual"
    physical = "physical"
    telepathic = "telepathic"


class AlienContact(BaseModel):
    contact_id: str = Field(min_length=3, max_length=15)
    timestamp: datetime
    location: str = Field(min_length=3, max_length=100)
    contact_type: ContactType
    signal_strength: float = Field(ge=0.0, le=10.0)
    duration_minutes: int = Field(ge=1, le=1440)
    witness_count: int = Field(ge=1, le=100)
    message_received: Optional[str] = Field(default=None, max_length=500)
    is_verified: bool = False

    @model_validator(mode="after")
    def check_contact_rules(self) -> "AlienContact":
        if not self.contact_id.startswith("AC"):
            raise ValueError("Contact_id must be start with 'AC'")
        if self.contact_type == ContactType.physical and not self.is_verified:
            raise ValueError("Physical must be verified")
        if (
            self.witness_count < 3
            and self.contact_type == ContactType.telepathic
        ):
            raise ValueError(
                "Telepathic contact requires at least 3 witnesses"
                )
        if self.signal_strength > 7.0 and not self.message_received:
            raise ValueError("Strong signals should include received messages")
        return self


def main() -> None:
    try:
        alien_Contact = AlienContact(
            contact_id="AC_2024_001",
            timestamp=datetime.now(),
            location=" Area 51, Nevada",
            contact_type=ContactType.radio,
            signal_strength=8.5,
            duration_minutes=45,
            witness_count=5,
            message_received="'Greetings from Zeta Reticuli'",
        )
        print("Alien Contact Log Validation")
        print("======================================")
        print("Valid contact report:")
        print(f"ID: {alien_Contact.contact_id}")
        print(f"Type: {alien_Contact.contact_type}")
        print(f"Location: {alien_Contact.location}")
        print(f"Signal: {alien_Contact.signal_strength}/10")
        print(f"Duration: {alien_Contact.duration_minutes} minutes")
        print(f"Witnesses: {alien_Contact.witness_count}")
        print(f"Message: {alien_Contact.message_received}\n")
    except ValidationError as e:
        print("======================================")
        print("Expected validation error:")
        for i in e.errors():
            print(i["msg"])

    try:
        alien_Contact = AlienContact(
            contact_id="AC_2024_001",
            timestamp=datetime.now(),
            location=" Area 51, Nevada",
            contact_type=ContactType.telepathic,
            signal_strength=8.5,
            duration_minutes=45,
            witness_count=2,
            message_received="'Greetings from Zeta Reticuli'",
        )
    except ValidationError as e:
        print("======================================")
        print("Expected validation error:")
        for i in e.errors():
            print(i["msg"].replace("Value error, ", ""))


if __name__ == "__main__":
    main()
