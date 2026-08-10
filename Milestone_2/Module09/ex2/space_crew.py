try:
    from pydantic import BaseModel, Field, ValidationError, model_validator
except ImportError:
    raise SystemExit(
        "You must use which Pydantic 2.x\n"
        "  Use: 'pip install pydantic >= 2'"
    )
from enum import Enum
from datetime import datetime


class Rank(Enum):
    cadet = "cadet"
    officer = "officer"
    lieutenant = "lieutenant"
    captain = "captain"
    commander = "commander"


class CrewMember(BaseModel):
    member_id: str = Field(min_length=3, max_length=10)
    name: str = Field(min_length=2, max_length=50)
    rank: Rank
    age: int = Field(ge=18, le=80)
    specialization: str = Field(min_length=3, max_length=30)
    years_experience: int = Field(ge=0, le=50)
    is_active: bool = True


class SpaceMission(BaseModel):
    mission_id: str = Field(min_length=5, max_length=15)
    mission_name: str = Field(min_length=3, max_length=100)
    destination: str = Field(min_length=3, max_length=50)
    launch_date: datetime
    duration_days: int = Field(ge=1, le=3650)
    crew: list[CrewMember] = Field(min_length=1, max_length=12)
    mission_status: str = "planned"
    budget_millions: float = Field(ge=1.0, le=10000.0)

    @model_validator(mode="after")
    def check_mission_rules(self) -> "SpaceMission":
        if not self.mission_id.startswith("M"):
            raise ValueError("Mission ID must start with M")

        has_leader = False
        for member in self.crew:
            if member.rank in (Rank.commander, Rank.captain):
                has_leader = True

        if not has_leader:
            raise ValueError("Must have at least one Commander or Captain")

        if self.duration_days > 365:
            experienced_count = 0
            for member in self.crew:
                if member.years_experience >= 5:
                    experienced_count += 1
            experienced_ratio = experienced_count / len(self.crew)

            if experienced_ratio < 0.5:
                raise ValueError(
                    "Long missions need 50% experienced crew (5+ years)"
                    )
        for member in self.crew:
            if not member.is_active:
                raise ValueError("All crew members must be active")

        return self


def main() -> None:
    try:
        print("Space Mission Crew Validation")
        print("=" * 40)
        print("Valid mission created:")
        commander = CrewMember(
            member_id="commander",
            name="Sarah Connor",
            rank=Rank.commander,
            age=42,
            specialization=" Mission Command",
            years_experience=15,
        )
        lieutenant = CrewMember(
            member_id="lieutenant",
            name="John Smith",
            rank=Rank.lieutenant,
            age=35,
            specialization="Navigation",
            years_experience=8,
        )
        officer = CrewMember(
            member_id="officer",
            name="Alice Johnson",
            rank=Rank.officer,
            age=28,
            specialization="Engineering",
            years_experience=5,
        )
        crew = [officer, lieutenant, commander]
        mission = SpaceMission(
            mission_id="M2024_MARS",
            mission_name=" Mars Colony Establishment",
            destination="Mars",
            launch_date=datetime.now(),
            duration_days=900,
            crew=crew,
            budget_millions=2500,
        )
        print(f"Mission: {mission.mission_name}")
        print(f"ID: {mission.mission_id}")
        print(f"Destination: {mission.destination}")
        print(f"Duration: {mission.duration_days} days")
        print(f"Budget: ${mission.budget_millions}M")
        print(f"Crew size: {len(crew)}")

        print("Crew members:")
        print(
            f"""- {commander.name} ({commander.rank})"""
            f""" - {commander.specialization}"""
        )

        print(
            f"""- {lieutenant.name} ({lieutenant.rank})"""
            f""" - {lieutenant.specialization}"""
        )

        print(
            f"""- {officer.name} ({officer.rank})"""
            f""" - {officer.specialization}"""
        )

        new_crew = CrewMember(
            member_id="herinaan",
            name="herinaan",
            rank=Rank.lieutenant,
            age=30,
            specialization=" None",
            years_experience=6,
        )
        _ = SpaceMission(
            mission_id="M2024_MARS",
            mission_name=" Mars Colony Establishment",
            destination="Mars",
            launch_date=datetime.now(),
            duration_days=900,
            crew=[new_crew],
            budget_millions=2500,
        )

    except ValidationError as e:
        print("\n=========================================")
        print("Expected validation error:")
        for i in e.errors():
            print(i["msg"])


if __name__ == "__main__":
    main()
