\name{delete.edge}
\alias{delete.edge}

\title{Delete Edge}

\description{
Delete an edge from an RHugin domain.
}

\usage{
delete.edge(domain, node, parent)
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{node}{a character string specifying the name of the child node in \code{domain} of the edge to be deleted.}
  \item{parent}{a character string specifying the name of the parent node in \code{domain} of the edge to be deleted.}
}

\details{
When an edge is removed, the table of \code{child} is adjusted as follows.  If \code{parent} is discrete, the contents of the updated table will be the portion of the old table corresponding to \code{parent} being in the first state; if \code{parent} is continuous, the beta parameters for the \code{parent -> child} edge will be deleted from the table.  Finally, \code{domain} is uncompiled by this operation.
}

\value{
a \code{NULL} value is invisibly returned.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/api-manuals}: \code{h_node_remove_parent}.
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

\examples{
# Create an RHugin domain
apple <- hugin.domain()

# Add nodes
add.node(apple, "Sick", states = c("yes", "no"))
add.node(apple, "Dry", states = c("yes", "no"))
add.node(apple, "Loses", states = c("yes", "no"))

# Add edges
add.edge(apple, "Loses", "Sick")
add.edge(apple, "Loses", "Dry")

# Delete the edge pointing from Sick to Loses
delete.edge(apple, "Loses", "Sick")
}

\keyword{programming}


