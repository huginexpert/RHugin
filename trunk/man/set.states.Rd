\name{set.states}
\alias{set.states}

\title{Set States}

\description{
Specify the states of a node.
}

\usage{
set.states(domain, node, states, subtype = "auto")
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{node}{a character string specifying the name of a node in \code{domain}.}
  \item{states}{a vector containing the states.}
  \item{subtype}{a character string specifying the subtype of the node. Possible subtypes are \code{labeled}, \code{boolean}, \code{numbered} and \code{interval}. The default choice \dQuote{auto} sets the subtype of the node to match the class of \code{states}: numeric and integer vectors result in a numbered node, logical vectors result in a boolean node, and all other vector types result in labeled nodes.  Otherwise the specified subtype is used and \code{states} is coerced as appropriate.}
}

\value{
a \code{NULL} value is invisibly returned.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/api-manuals}: \code{h_node_set_number_of_states}, \code{h_node_set_state_label} and \code{h_node_set_state_value}.
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

\examples{
# Create an RHugin domain
apple <- hugin.domain()

# Add nodes without specifying states
add.node(apple, "Sick")
add.node(apple, "Dry")
add.node(apple, "Loses")

# Specify states for each node
set.states(apple, "Sick", states = c("yes", "no"))
set.states(apple, "Dry", states = c("yes", "no"))
set.states(apple, "Loses", states = c("yes", "no"))
}

\keyword{programming}


