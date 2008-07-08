\name{delete.edge}
\alias{delete.edge}

\title{Delete Edges}

\description{
Delete edges from an RHugin domain object.
}

\usage{
delete.edge(domain, child, parent)
}

\arguments{
  \item{domain}{an RHugin domain object.}
  \item{child}{a character vector of length one specifying the name of the child node in \code{domain} of the edge to be deleted.}
  \item{parent}{a character vector of length one specifying the name of the parent node in \code{domain} of the edge to be deleted.}
}

\details{
When an edge is removed, the table of \code{child} is adjusted as follows.  If \code{parent} is discrete, the contents of the updated table will be the portion of the old table corresponding to \code{parent} being in the first state; if \code{parent} is continuous, the beta parameters for the \code{parent -> child} edge will be deleted from the table.  Finally, \code{domain} is uncompiled by this operation.
}

\value{
a \code{NULL} value is invisibly returned.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
  \code{\link{add.edge}},
  \code{\link{get.edges}},
  \code{\link{reverse.edge}}.
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

# Delete an edge
delete.edge(AppleTree, "Loses", "Sick")
}

\keyword{programming}


