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
  \item{domain}{an RHugin domain.}
  \item{node}{a character string specifying the name of a node in \code{domain}.}
  \item{values}{a logical value that applies to interval nodes only. If \code{TRUE} the endpoints of the intervals are returned in a numeric vector.}
}

\value{
a vector containing the states of the selected node.
}

\references{
HUGIN API Reference Manual \url{http://download.hugin.com/webdocs/manuals/api-manual.pdf}: \code{h_node_get_number_of_states}, \code{h_node_get_state_label} and \code{h_node_get_state_value}.
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

\examples{
# Create an RHugin domain
apple <- hugin.domain()

# Add nodes
add.node(apple, "Sick", states = c("yes", "no"))
add.node(apple, "Dry", states = c("yes", "no"))
add.node(apple, "Loses", states = c("yes", "no"))

# List the states of the node "Loses"
get.states(apple, "Loses")
}

\keyword{programming}


