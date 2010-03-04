library(RHugin, lib.loc = "../")
demo("asia", echo = FALSE)

compile(asia)

set.finding(asia, "Asia", "yes")
set.finding(asia, "Dyspnoea", "yes")

propagate(asia)

get.belief(asia, "Asia")
get.belief(asia, "Smoking")
get.belief(asia, "Tuberculosis")
get.belief(asia, "LungCancer")
get.belief(asia, "Bronchitis")
get.belief(asia, "Either")
get.belief(asia, "XRay")
get.belief(asia, "Dyspnoea")


