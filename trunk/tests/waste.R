library(RHugin, lib.loc = "../")
demo("buildWasteNetwork", echo = FALSE)

compile(waste)

set.finding(waste, "Type", "industrial")
set.finding(waste, "Light", 1.1)
set.finding(waste, "CO2", -0.9)

propagate(waste)

get.belief(waste, "Burn")
get.belief(waste, "Filter")
get.belief(waste, "Type")
get.belief(waste, "Efficiency")
get.belief(waste, "Dust")
get.belief(waste, "CO2")
get.belief(waste, "Light")
get.belief(waste, "Metal")
get.belief(waste, "Emission")


