\name{retract}
\alias{retract}

\title{Retract Evidence}

\description{
Retract evidence from one node or all nodes in an RHugin domain.
}

\usage{
retract(domain, node)
}

\arguments{
  \item{domain}{an RHugin domain object.}
  \item{node}{an optional character vector of length one specifying the name of the node for which evidence is to be retracted.}
}

\details{
The \code{node} argument is optional.  If only \code{domain} is given then evidence is retracted from all nodes in the domain.
}

\value{
a \code{NULL} value is invisibly returned.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
  \code{\link{hugin.domain}},
  \code{\link{set.finding}},
  \code{\link{initialize.domain}}.
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

# Retract evidence from Dry and propagate
retract(AppleTree, "Dry")
propagate(AppleTree)
get.belief(AppleTree, "Sick")

# Retract all evidence and propagate
retract(AppleTree)
propagate(AppleTree)
get.belief(AppleTree, "Sick")
}

\keyword{programming}


