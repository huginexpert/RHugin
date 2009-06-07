\name{add.node}
\alias{add.node}

\title{Add Node}

\description{
Add a node to an RHugin domain object.
}

\usage{
add.node(domain, name,
         category = c("chance", "decision", "utility"),
         kind = c("discrete", "continuous"),
         states)
}

\arguments{
  \item{domain}{an RHugin domain object.}
  \item{name}{a character string specifying the name of the new node (see details).}
  \item{category}{a character string specifying the category of the node.}
  \item{kind}{a character string specifying the kind of the node.}
  \item{states}{an optional vector of states for the node.  The subtype of the node is inferred from the class of \code{states}: a character vector results in a labeled node, a numeric (or integer) vector results in a numbered node and a logical vector results in a boolean node. Be aware that the states of a boolean node are \code{FALSE} and \code{TRUE} in that order regardless of the value of \code{states}.}
}

\details{
The name of the node must be a valid identifier in the C programming language.  In particular the name must start with a letter and contain no white space.  Additionally, the words \dQuote{Freq}, \dQuote{Value}, \dQuote{Cost} and \dQuote{Utility} are reserved and cannot be used as the name of a node.
}

\value{
a \code{NULL} value is invisibly returned.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/API_Manuals/}: \code{h_domain_new_node}, \code{h_node_set_name} and \code{h_node_set_subtype}.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
  \code{\link{set.states}}.
}

\examples{
# Create an RHugin domain
AppleTree <- hugin.domain()

# Add nodes
add.node(AppleTree, "Sick", states = c("yes", "no"))
add.node(AppleTree, "Dry", states = c("yes", "no"))
add.node(AppleTree, "Loses", states = c("yes", "no"))
}

\keyword{programming}


