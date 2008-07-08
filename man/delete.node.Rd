\name{delete.node}
\alias{delete.node}

\title{Delete Node}

\description{
Delete a node from an RHugin domain object.
}

\usage{
delete.node(domain, node)
}

\arguments{
  \item{domain}{an RHugin domain object.}
  \item{node}{a character vector of length one containing the name of the node in \code{domain} to be deleted.}
}

\details{
All of the edges in the RHugin domain involving \code{node} are deleted as well.  If \code{node} has any children their conditional probability tables (CPT) are adjusted: if \code{node} is discrete, the contents of the updated table will be the portion of the old CPT corresponding to \code{node} being in the first state; if \code{node} is continuous, the beta parameters for the \code{node -> child} edge will be deleted from the table.  Finally, \code{domain} is uncompiled by this operation.
}

\value{
a \code{NULL} value is invisibly returned.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
  \code{\link{add.node}}.
}

\examples{
# Create an RHugin domain
AppleTree <- hugin.domain()

# Add some nodes
add.node(AppleTree, "Sick", states = c("yes", "no"))
add.node(AppleTree, "Dry", states = c("yes", "no"))
add.node(AppleTree, "Loses", states = c("yes", "no"))

# Delete "Dry"
delete.node(AppleTree, "Dry")
}

\keyword{programming}


