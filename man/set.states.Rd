\name{set.states}
\alias{set.states}

\title{Set States}

\description{
Specify the states of a node.
}

\usage{
set.states(domain, node, states)
}

\arguments{
  \item{domain}{an RHugin domain object.}
  \item{node}{a character vector of length one containing the name of a node in \code{domain}.}
  \item{states}{a character vector specifying the names of the states.}
}

\value{
a \code{NULL} value is invisibly returned.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
  \code{\link{hugin.domain}},
  \code{\link{add.node}}.
}

\examples{
# Create an RHugin domain
AppleTree <- hugin.domain()

# Add the nodes without specifying states
add.node(AppleTree, "Sick")
add.node(AppleTree, "Dry")
add.node(AppleTree, "Loses")

# Specify the states of the nodes
set.states(AppleTree, "Sick", states = c("yes", "no"))
set.states(AppleTree, "Dry", states = c("yes", "no"))
set.states(AppleTree, "Loses", states = c("yes", "no"))
}

\keyword{programming}


