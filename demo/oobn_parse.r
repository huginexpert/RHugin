library(RHugin)

file_name <- "./demo/test_oobn.oobn"
class_name <- "test_oobn"
time_slices <- 1

# Load class collection from file name
cc <- hugin.class.collection.parse(file_name)

# Get class by name
class <- hugin.class.collection.get.class.by_name(cc, class_name)

# Create DBN
dbn <- hugin.domain.dbn(class, time_slices)
compile.RHuginDomain(dbn)

# Add evidence
set.finding(dbn, "T1.smell", "bad")

# Propagate
propagate.RHuginDomain(dbn)

# Get first time window result
fan_power <- get.belief(dbn, "T1.fan_power")

# Move time window and propagate
hugin.domain.dbn.move(dbn, 1)
propagate.RHuginDomain(dbn)

# Get second time window result
fan_power_again <- get.belief(dbn, "T1.fan_power")
