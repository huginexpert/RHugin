library(RHugin, lib.loc = "../")
demo("buildChestClinicNetwork", echo = FALSE)

compile(ChestClinic)

set.finding(ChestClinic, "Asia", "yes")
set.finding(ChestClinic, "Dyspnoea", "yes")

propagate(ChestClinic)

get.belief(ChestClinic, "Asia")
get.belief(ChestClinic, "Smoking")
get.belief(ChestClinic, "Tuberculosis")
get.belief(ChestClinic, "LungCancer")
get.belief(ChestClinic, "Bronchitis")
get.belief(ChestClinic, "Either")
get.belief(ChestClinic, "XRay")
get.belief(ChestClinic, "Dyspnoea")


