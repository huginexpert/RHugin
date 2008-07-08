library(MASS)
data(housing)

hd <- hugin.domain()
generate.nodes(hd, housing)

add.edge(hd, "Cont", "Type")
add.edge(hd, "Sat", "Cont")
add.edge(hd, "Sat", "Infl")
add.edge(hd, "Sat", "Type")

generate.tables(hd, housing)

compile(hd)
set.finding(hd, "Sat", "High")
get.belief(hd, "Type")

