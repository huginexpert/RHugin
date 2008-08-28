\name{initialize.domain}
\alias{initialize.domain}

\title{Initialize a Domain}

\description{
Establish the initial values for all evidence, belief and junction tree tables in an RHugin domain.
}

\usage{
initialize.domain(domain)
}

\arguments{
  \item{domain}{an RHugin domain object.}
}

\details{
If an up-to-date memory backup exists (when \code{save = TRUE} in \code{\link{propagate}}) then the initialization is accomplished simply by loading the tables from the backup.  Otherwise, the initial values are recomputed from the conditional probability and utility potentials.  This function erases all previously entered evidence.
}

\value{
a \code{NULL} value is invisibly returned.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
  \code{\link{hugin.domain}},
  \code{\link{set.finding}},
  \code{\link{retract}}.
}

\examples{
# Create an RHugin domain
AppleTree <- hugin.domain()

# Add the nodes
add.node(AppleTree, "Sick", states = c("yes", "no"))
add.node(AppleTree, "Dry", states = c("yes", "no"))
add.node(AppleTree, "Loses", states = c("yes", "no"))

# Add the edges
add.edge(AppleTree, "Loses", "Sick")
add.edge(AppleTree, "Loses", "Dry")

# Enter the conditional probability tables
sick.table <- get.table(AppleTree, "Sick")
sick.table[, 2] <- c(0.1, 0.9)
set.table(AppleTree, "Sick", sick.table)

dry.table <- get.table(AppleTree, "Dry")
dry.table[, 2] <- c(0.1, 0.9)
set.table(AppleTree, "Dry", dry.table)

loses.table <- get.table(AppleTree, "Loses")
loses.table[, 4] <- c(0.95, 0.05, 0.90, 0.10, 0.85, 0.15, 0.02, 0.98)
set.table(AppleTree, "Loses", loses.table)

# Compile the domain
compile(AppleTree)

# Select states
set.finding(AppleTree, "Dry", "no")
set.finding(AppleTree, "Loses", "yes")

# Propagate and get beliefs
propagate(AppleTree)
get.belief(AppleTree, "Sick")

# Initialize the domain
initialize.domain(AppleTree)
}

\keyword{programming}


