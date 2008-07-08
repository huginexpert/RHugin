\name{add.edge}
\alias{add.edge}

\title{Adding Edges}

\description{
Add a directed edge from the node \code{parent} to the node \code{child}.
}

\usage{
add.edge(domain, child, parent)
}

\arguments{
  \item{domain}{an RHugin domain object.}
  \item{child}{a character vector of length one containing the name of the child node.}
  \item{parent}{a character vector of length one containing the name of the parent node.}
}

\value{
a \code{NULL} value is invisibly returned.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
  \code{\link{hugin.domain}},
  \code{\link{set.finding}},
  \code{\link{propagate}}.
}

\examples{
# Create an RHugin domain
AppleTree <- hugin.domain()

# Add the nodes
add.node(AppleTree, "Sick", states = c("sick", "not sick"))
add.node(AppleTree, "Dry", states = c("dry", "not dry"))
add.node(AppleTree, "Loses", states = c("loses", "keeps"))

# Add the edges
add.edge(AppleTree, "Loses", "Sick")
add.edge(AppleTree, "Loses", "Dry")
}

\keyword{programming}


