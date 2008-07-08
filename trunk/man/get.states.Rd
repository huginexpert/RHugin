\name{get.states}
\alias{get.states}

\title{Get States}

\description{
List the states of a node.
}

\usage{
get.states(domain, node)
}

\arguments{
  \item{domain}{an RHugin domain object.}
  \item{node}{a character vector of length one containing the name of a node in \code{domain}.}
}

\value{
a character vector containing the names of the states of the selected node.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
  \code{\link{hugin.domain}},
  \code{\link{add.node}}.
}

\examples{
# Create an RHugin domain
AppleTree <- hugin.domain()

# Add some nodes
add.node(AppleTree, "Sick", states = c("yes", "no"))
add.node(AppleTree, "Dry", states = c("yes", "no"))
add.node(AppleTree, "Loses", states = c("yes", "no"))

# List the states of the node "Loses"
get.states(AppleTree, "Loses")
}

\keyword{programming}


