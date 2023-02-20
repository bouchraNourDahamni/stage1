from enum import Enum


class Length(Enum):
    FourtyFive = "forty five"
    BadLength = "BadLength"
    Eighteen = "eighteen"
    Twenty = "twenty"
    TwentyTwo = "twenty two"
    TwentyFour = "twenty four"
    Twentysix = "twenty six"
    TwentyEight = "twenty eight"
    Ten = "ten"
    Twelve = "twelve"
    Fourteen = "fourteen"
    ThirtyTwo = "thirty two"
    Thirty = "thirty"
    ThirtyFive = "thirty five"
    ThirtyFour = "thirty four"
    ThirtyEight = "thirty eight"
    Thirtysix = "thirty six"
    FourtySix = "forty six"
    FourtyTwo = "forty two"
    FourtyFour = "forty four"
    FourtyEight = "forty eight"
    Fourty = "forty"
    FiftyFive = "fifty five"
    FiftyFour = "fifty four"
    Fifty = "fifty"
    FiftyTwo = "fifty two"
    FiftySix = "fifty six"
    FiftyEight = "fifty eight"
    Sixty = "sixty"
    SixtyFour = "sixty four"
    SixtySix = "sixty six"
    SixtyEight = "sixty eight"
    Seventy = "seventy"
    SeventyFive = "seventy five"
    SixtyFive = "sixty five"
    Eighty = "eighty"
    Eleven = "eleven"
    Fifteen = "fifteen"
    Nineteen = "nineteen"
    Three = "three"
    ThreePointFive = "three point five"
    ThreePointEight = "three point eight"
    Cylinder = "cylinder"
    OnePointEight = "one point eight"
    TwoPointThree = "two point three"
    TwoPointFive = "two point five"
    One = "one"
    Two = "two"
    Four = "four"
    Five = "five"
    Seven = "seven"
    TwoPointEight = "two point eight"
    ThreePointTwo = "three point two"
    FourPointFive = "four point five"
    Six = "six"
    Eight = "eight"
    Nine = "nine"
    Thirteen = "thirteen"
    Sixteen = "sixteen"
    SixPointFour = "six point four"
    FourPointThree = "four point three"
    SixteenPointSeven = "sixteen point seven"


class DiameterScrew(Enum):
    ThreePointFive = "three point five"
    FourPointFive = "four point five"
    FivePointFive = "five point five"
    SixPointFive = "six point five"
    SevenPointFive = "seven point five"
    BadDiameter = "BadDiameter"

class ThreadFullness(Enum):
    BadThreadFulness = []
    PartiallyThreaded = ["partially threaded", "partially", "part"]
    FullyThreaded = ["fully threaded", "fully", "full"]

class HeadType(Enum):
    BadHeadType = []
    NonLockingCross = ["non locking cross", "nonlocking", "nonlocking", "non loocking", "none looking", "non loock",
                       "not looking", "know looking", "non locking", "non looking"]
    Locking = ["locking", "look"]


class UpdatePropertyType(Enum):
    UpdateHeadType = 1
    UpdateThreadFulness = 2
    UpdateLength = 3


class ThreadType(Enum):
    BadThreadType = "BadThreadType "
    Cancellous = "cancellous"
    Cortical = "cortical"


class ScrewWrist:
    def __init__(self, thread_fullness, head_type):
        self.thread_fullness_ = thread_fullness
        self.head_type_ = head_type

    def __hash__(self):
        return hash((self.thread_fullness_, self.head_type_))

    def __eq__(self, other_screw_wrist):
        return (self.thread_fullness_, self.head_type_) == (
            other_screw_wrist.thread_fullness_, other_screw_wrist.head_type_)

    def __ne__(self, other_screw_wrist):
        return not (self == other_screw_wrist)
