\name{clone.node}
\alias{clone.node}

\title{Clone Node}

\description{
Add a copy of a node to an RHugin domain.
}

\usage{
clone.node(domain, node, name)
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{node}{a character string specifying the name of the node in \code{domain} to be cloned.}
  \item{name}{a character string specifying the name of the clone.}
}

\details{
The components of the cloned node are identical to those of \code{node}: category, kind, subtype, number of states, state labels, state values, parents, tables, case data, and evidence.  The cloned node will not have any children as this would imply changes to the children.
}

\value{
a \code{NULL} value is invisibly returned.
}

\references{
HUGIN API Reference Manual \url{http://download.hugin.com/webdocs/manuals/api-manual.pdf}: \code{h_node_clone}.
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

\examples{
# Create an RHugin domain
apple <- hugin.domain()

# Add some nodes
add.node(apple, "Sick", states = c("yes", "no"))
add.node(apple, "Loses", states = c("yes", "no"))

# Clone "Sick"
clone.node(apple, "Sick", "Dry")
}

\keyword{programming}


