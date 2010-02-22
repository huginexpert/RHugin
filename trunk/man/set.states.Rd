\name{set.states}
\alias{set.states}

\title{Set States}

\description{
Specify the states of a node.
}

\usage{
set.states(domain, node, states, subtype = c("auto", "labeled",
          "boolean", "numbered", "interval"))
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{node}{a character string specifying the name of a node in \code{domain}.}
  \item{states}{a vector containing the states.}
  \item{subtype}{the default choice \dQuote{auto} sets the subtype of the node to match the class of \code{states}: numeric and integer vectors result in a numbered node, logical vectors result in a boolean node, and all other vector types result in labeled nodes.  Otherwise the specified subtype is used and \code{states} is coerced as appropriate.}
}

\value{
a \code{NULL} value is invisibly returned.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/api-manuals}: \code{h_node_set_number_of_states}, \code{h_node_set_state_label} and \code{h_node_set_state_value}.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\examples{
# Create an RHugin domain
AppleTree <- hugin.domain()

# Add nodes without specifying states
add.node(AppleTree, "Sick")
add.node(AppleTree, "Dry")
add.node(AppleTree, "Loses")

# Specify states for each node
set.states(AppleTree, "Sick", states = c("yes", "no"))
set.states(AppleTree, "Dry", states = c("yes", "no"))
set.states(AppleTree, "Loses", states = c("yes", "no"))
}

\keyword{programming}


