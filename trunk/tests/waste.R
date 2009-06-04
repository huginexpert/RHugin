library(RHugin, lib.loc = "../")
waste <- hugin.domain()

add.node(waste, "Type", states = c("industrial", "household"))
add.node(waste, "Filter", states = c("intact", "defective"))
add.node(waste, "Burn", states = c("stable", "unstable"))

add.node(waste, "Metal", kind = "continuous")
add.node(waste, "Efficiency", kind = "continuous")
add.node(waste, "CO2", kind = "continuous")
add.node(waste, "Dust", kind = "continuous")
add.node(waste, "Emission", kind = "continuous")
add.node(waste, "Light", kind = "continuous")

add.edge(waste, "Metal", "Type")
add.edge(waste, "Efficiency", c("Type", "Filter"))
add.edge(waste, "CO2", "Burn")
add.edge(waste, "Dust", c("Type", "Efficiency", "Burn"))
add.edge(waste, "Emission", c("Metal", "Dust"))
add.edge(waste, "Light", "Dust")

Type.table <- get.table(waste, "Type")
Type.table[["Freq"]] <- c(2/7, 5/7)
set.table(waste, "Type", Type.table)

Filter.table <- get.table(waste, "Filter")
Filter.table[["Freq"]] <- c(0.95, 0.05)
set.table(waste, "Filter", Filter.table)

Burn.table <- get.table(waste, "Burn")
Burn.table[["Freq"]] <- c(0.85, 0.15)
set.table(waste, "Burn", Burn.table)

Metal.table <- get.table(waste, "Metal")
Metal.table[["Value"]] <- c(0.5, 0.01, -0.5, 0.005)
set.table(waste, "Metal", Metal.table)

Efficiency.table <- get.table(waste, "Efficiency")
Efficiency.table[["Value"]] <- c(-3.9, 0.00002, -3.2, 0.00002, -0.4, 0.0001, -0.5, 0.0001)
set.table(waste, "Efficiency", Efficiency.table)

CO2.table <- get.table(waste, "CO2")
CO2.table[["Value"]] <- c(-2.0, 0.1, -1.0, 0.3)
set.table(waste, "CO2", CO2.table)

Dust.table <- get.table(waste, "Dust")
Dust.table[["Value"]] <- c(6.5, 1.0, 0.03, 6.0, 1.0, 0.04, 7.5, 1.0, 0.1, 7.0, 1.0, 0.1)
set.table(waste, "Dust", Dust.table)

Emission.table <- get.table(waste, "Emission")
Emission.table[["Value"]] <- c(0.0, 1.0, 1.0, 0.002)
set.table(waste, "Emission", Emission.table)

Light.table <- get.table(waste, "Light")
Light.table[["Value"]] <- c(3.0, -0.5, 0.25)
set.table(waste, "Light", Light.table)

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


