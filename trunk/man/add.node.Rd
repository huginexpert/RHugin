\name{add.node}
\alias{add.node}

\title{Add Nodes}

\description{
Add a node to an RHugin domain object.
}

\usage{
add.node(domain, name,
         category = c("chance", "decision", "utility", "instance"),
         kind = c("discrete", "continuous"),
         subtype = c("labeled", "boolean", "numbered", "interval"),
         states)
}

\arguments{
  \item{domain}{an RHugin domain object.}
  \item{name}{a character string specifying the name of the new node (see details).}
  \item{category}{a character string specifying the category of the node.}
  \item{kind}{a character string specifying the kind of the node.}
  \item{subtype}{a character string specifying the subtype of the node.}
  \item{states}{an optional vector of states for the node.  The type of vector should be appropriate for the subtype of the node: character for labeled node or numeric for numbered and interval nodes.  Boolean nodes automatically have their states set to \code{FALSE} and \code{TRUE}.  See the function \code{\link{set.states}} for further details.}
}

\details{
The name of the node must be a valid identifier in the C programming language.  In particular the name must start with a letter and contain no white space.
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


