from enum import Enum


class ToolHandleType(Enum):
    ActuatedStraight = "Actuated Straight"
    StraightClosing = "Straight Closing"
    AngledClosing = "Angled Closing"
    Straight = "Straight"
    Pistol = "Pistol"
    BadToolHandle = "Bad Tool Handle"
