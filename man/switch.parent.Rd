\name{switch.parent}
\alias{switch.parent}

\title{Switch Parent}

\description{
Switch parents for a node in an RHugin domain.
}

\usage{
switch.parent(domain, child, parent, new.parent)
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{child}{a character string specifying the name of a child node in \code{domain}.}
  \item{parent}{a character string specifying the name of a current parent node of \code{child}.}
  \item{new.parent}{a character string specifying the name of a node in \code{domain} that is to be the new parent of \code{child}.}
}

\details{
Substitute \code{new.parent} for \code{parent} as the parent of \code{child} while preserving the validity of the table of \code{child}.  The \code{parent} and \code{new.parent} nodes must be compatible.  Compatible nodes have (1) the same category and kind, (2) the same subtype and number of states (if discrete), (3) the same list of state labels (if the nodes are labeled) and (4) the same list of state values (if the nodes are numbered or of interval subtype).
}

\value{
a \code{NULL} value is invisibly returned.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/api-manuals}: \code{h_node_switch_parent}.
}

\author{Kjell Konis \email{kjell.konis@me.com}}

\examples{
# Create an RHugin domain
apple <- hugin.domain()

# Add nodes
add.node(apple, "Sick", states = c("yes", "no"))
add.node(apple, "Dry", states = c("yes", "no"))
add.node(apple, "Loses", states = c("yes", "no"))

# Add an edge
add.edge(apple, "Loses", "Dry")

# Switch parent of Loses to Sick
switch.parent(apple, "Loses", "Dry", "Sick")
}

\keyword{programming}


