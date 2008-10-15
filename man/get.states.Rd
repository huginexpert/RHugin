\name{get.states}
\alias{get.states}

\title{Get States}

\description{
List the states of a node.
}

\usage{
get.states(domain, node, values = FALSE)
}

\arguments{
  \item{domain}{an RHugin domain object.}
  \item{node}{a character string specifying the name of a node in \code{domain}.}
  \item{values}{a logical value that applies to interval nodes only. If \code{TRUE} the endpoints of the intervals are returned in a numeric vector.}
}

\value{
a vector containing the states of the selected node.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/API_Manuals/}: \code{h_node_get_number_of_states}, \code{h_node_get_state_label} and \code{h_node_get_state_value}.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\examples{
# Create an RHugin domain
AppleTree <- hugin.domain()

# Add nodes
add.node(AppleTree, "Sick", states = c("yes", "no"))
add.node(AppleTree, "Dry", states = c("yes", "no"))
add.node(AppleTree, "Loses", states = c("yes", "no"))

# List the states of the node "Loses"
get.states(AppleTree, "Loses")
}

\keyword{programming}


