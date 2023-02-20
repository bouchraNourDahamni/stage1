from Tool import Tool
from ToolWithSizes import ToolWithSizes
from Feature import Feature
from ToolHandleType import ToolHandleType
from ToolProperties import Length
from ToolProperties import DiameterScrew
from ToolProperties import ScrewWrist
from ToolProperties import HeadType
from ToolProperties import ThreadFullness
from ToolProperties import ThreadType
from Screw import Screw

toolListSpine = [
    ToolWithSizes(["scalpel"], ToolHandleType.ActuatedStraight,
                  [Length.Ten, Length.Eleven, Length.Twelve, Length.Fifteen, Length.Nineteen]),
    ToolWithSizes(["awl"], ToolHandleType.StraightClosing, [
        Length.ThreePointFive, Length.ThreePointEight, Length.Three]),
    ToolWithSizes(["burr"], ToolHandleType.ActuatedStraight, [Length.Cylinder, Length.Three, Length.Four]),
    ToolWithSizes(["drill"], ToolHandleType.ActuatedStraight,
                  [Length.OnePointEight, Length.TwoPointThree, Length.TwoPointFive, Length.ThreePointFive]),
    ToolWithSizes(["kerrison punch", "kerrison", "punch"], ToolHandleType.AngledClosing,
                  [Length.One, Length.Two, Length.Three, Length.Four, Length.Five]),
    ToolWithSizes(["pedicle finder", "finder", "pedicle"], ToolHandleType.Straight,
                  [Length.TwoPointEight, Length.ThreePointFive, Length.Two]),
    Screw(["screwdriver", "screw"], ToolHandleType.Pistol),
    Tool(["ball tip probe", "probe", "ball", "tip"], ToolHandleType.Straight),
    Tool(["bone nibbler", "nibbler"], ToolHandleType.StraightClosing),
    Tool(["disc rongeur", "disc"], ToolHandleType.Straight),
    Tool({"nerve hook", "nerve", "hook"}, ToolHandleType.ActuatedStraight),
    Tool(["bone curette", "curette"], ToolHandleType.ActuatedStraight),
    ToolWithSizes(["pituitary rongeur", "pituitary", "rongeur"], ToolHandleType.AngledClosing,
                  [Length.One, Length.Two, Length.Three, Length.Four, Length.Five])
]

toolListTrauma = [
    ToolWithSizes(["drill"], ToolHandleType.Pistol,
                  [Length.TwoPointFive, Length.ThreePointTwo, Length.ThreePointFive, Length.FourPointFive, Length.Two]),
    Tool(["depth gauge", "depth", "gauge"], ToolHandleType.ActuatedStraight),
    ToolWithSizes(["plate"], ToolHandleType.Straight,
                  [Length.Three, Length.Four, Length.Five, Length.Six, Length.Seven, Length.Eight, Length.Nine]),
]

toolListReconstruction = [
    ToolWithSizes(["saw"], ToolHandleType.StraightClosing, [Length.Fourteen, Length.Eighteen]),
    ToolWithSizes(["burr"], ToolHandleType.ActuatedStraight, [Length.Cylinder, Length.Three, Length.Four]),
    Tool(["bone nibbler", "nibbler"], ToolHandleType.StraightClosing)
]

ScrewSpineCommonLength = [Length.ThirtyFive,
                          Length.FourtyFive,
                          Length.FiftyFive, Length.Sixty, Length.Thirty, Length.Fourty, Length.Fifty]

ScrewSpineData = {
    DiameterScrew.ThreePointFive: [Length.Ten,
                                   Length.Twelve, Length.Fourteen, Length.Sixteen, Length.Eighteen,
                                   Length.TwentyTwo, Length.TwentyFour, Length.Twentysix,
                                   Length.TwentyEight, Length.Thirty, Length.Twenty],
    DiameterScrew.FourPointFive: [Length.ThirtyFive, Length.FourtyFive,
                                  Length.Fifty, Length.Thirty, Length.Fourty],

    DiameterScrew.FivePointFive: ScrewSpineCommonLength,
    DiameterScrew.SixPointFive: ScrewSpineCommonLength,
    DiameterScrew.SevenPointFive: ScrewSpineCommonLength,
}

screwWristCommonLength = [Length.Ten, Length.Twelve, Length.Fourteen, Length.Sixteen, Length.Eighteen,
                          Length.TwentyTwo, Length.TwentyFour, Length.Twentysix, Length.TwentyEight,
                          Length.ThirtyTwo, Length.ThirtyFour, Length.Thirtysix, Length.ThirtyEight,
                          Length.Twenty, Length.Thirty]

screwWristData = {
    ScrewWrist(ThreadFullness.PartiallyThreaded, HeadType.NonLockingCross): [Length.Sixteen, Length.Eighteen,
                                                                             Length.Twenty, Length.TwentyTwo,
                                                                             Length.TwentyFour, Length.Twentysix],
    ScrewWrist(ThreadFullness.FullyThreaded, HeadType.NonLockingCross): screwWristCommonLength,
    ScrewWrist(ThreadFullness.PartiallyThreaded, HeadType.Locking): [Length.Twenty, Length.TwentyTwo, Length.TwentyFour,
                                                                     Length.Twentysix],
    ScrewWrist(ThreadFullness.FullyThreaded, HeadType.Locking): screwWristCommonLength
}

screwAnkleData = {
    ThreadType.Cancellous: [Length.ThirtyTwo, Length.ThirtyFour, Length.Thirtysix,
                            Length.ThirtyEight, Length.ThirtyTwo, Length.ThirtyFour,
                            Length.ThirtyEight, Length.FourtyTwo, Length.FourtyFour, Length.FourtySix,
                            Length.FiftyTwo,
                            Length.FiftyFour, Length.FiftySix, Length.FiftyEight,
                            Length.SixtyFour, Length.SixtySix, Length.SixtyEight, Length.Seventy, Length.Thirty,
                            Length.Fourty, Length.Sixty,
                            Length.Fifty],
    ThreadType.Cortical: [Length.Ten, Length.Twelve, Length.Fourteen, Length.Sixteen,
                          Length.Eighteen, Length.TwentyTwo, Length.TwentyFour, Length.Twentysix,
                          Length.TwentyEight, Length.ThirtyTwo, Length.ThirtyFour, Length.Thirtysix,
                          Length.ThirtyEight, Length.FourtyTwo,
                          Length.FourtyFour, Length.FourtySix, Length.FourtyEight,
                          Length.FiftyTwo, Length.FiftyFour, Length.FiftySix, Length.FiftyEight,
                          Length.SixtyFive, Length.SeventyFive, Length.Eighty, Length.Twenty, Length.Thirty,
                          Length.Fourty, Length.Fifty, Length.Sixty, Length.Seventy]
}

otherFeatures = [
    Feature(["xray", "ray", "shoot"], "I took an xray"),
    Feature(["green", "remove green guide"], "I removed green guide"),
    Feature(["flip", "flip patient"], "I flipped patient")
]
