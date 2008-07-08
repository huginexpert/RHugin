\name{get.nodes}
\alias{get.nodes}

\title{Get Nodes}

\description{
List the nodes in an RHugin domain object.
}

\usage{
get.nodes(domain)
}

\arguments{
  \item{domain}{an RHugin domain object.}
}

\value{
a character vector containing the names of the nodes in the RHugin domain.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
  \code{\link{hugin.domain}},
  \code{\link{add.node}}.
}

\examples{
# Create an RHugin domain
AppleTree <- hugin.domain()

# Add the nodes
add.node(AppleTree, "Sick", states = c("yes", "no"))
add.node(AppleTree, "Dry", states = c("yes", "no"))
add.node(AppleTree, "Loses", states = c("yes", "no"))

# List the nodes in AppleTree
get.nodes(AppleTree)
}

\keyword{programming}


