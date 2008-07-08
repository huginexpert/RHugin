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
  \item{name}{a character vector of length one specifying the name of the new node (see details).}
  \item{category}{a character vector of length one specifying the category of the node.}
  \item{kind}{a character vector of length one specifying the kind of the node.}
  \item{subtype}{a character vector of length one specifying the subtype of the node.}
  \item{states}{an optional character vector specifying the states of the node.  The states of the node may be specified later or changed using the \code{\link{set.states}} function.}
}

\details{
The name of the node must be a valid identifier in the C programming language.  In particular the name must start with a letter and contain no white space.
}

\value{
a \code{NULL} value is invisibly returned.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
  \code{\link{hugin.domain}},
  \code{\link{set.states}}.
}

\examples{
# Create an RHugin domain
AppleTree <- hugin.domain()

# Add some nodes
add.node(AppleTree, "Sick", states = c("yes", "no"))
add.node(AppleTree, "Dry", states = c("yes", "no"))
add.node(AppleTree, "Loses", states = c("yes", "no"))
}

\keyword{programming}


