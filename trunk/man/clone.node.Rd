\name{clone.node}
\alias{clone.node}

\title{Clone Nodes}

\description{
Clone a node in an RHugin domain object.
}

\usage{
clone.node(domain, node, new.name)
}

\arguments{
  \item{domain}{an RHugin domain object.}
  \item{node}{a character vector of length one giving the name of the node in \code{domain} to be cloned.}
  \item{new.name}{a character vector of length one specifying the name of the cloned node.}
}

\details{
The components of the cloned node are identical to those of \code{node}: category, kind, subtype, number of states, state labels, state values, parents, tables, case data, and evidence.  The cloned node will not have any children as this would imply changes to the children.
}

\value{
a \code{NULL} value is invisibly returned.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
  \code{\link{add.node}},
  \code{\link{get.nodes}},
  \code{\link{delete.node}}.
}

\examples{
# Create an RHugin domain
AppleTree <- hugin.domain()

# Add some nodes
add.node(AppleTree, "Sick", states = c("yes", "no"))
add.node(AppleTree, "Loses", states = c("yes", "no"))

# Clone "Sick"
clone.node(AppleTree, "Sick", "Dry")
}

\keyword{programming}


