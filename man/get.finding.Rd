\name{get.finding}
\alias{get.finding}

\title{Get Entered Finding}

\description{
Retrieve entered findings from a node in an RHugin domain object.
}

\usage{
get.finding(domain, node)
}

\arguments{
  \item{domain}{an RHugin domain object.}
  \item{node}{a character string specifying the name of the node from which the entered findings are to be retrieved.}
}

\value{
  a numeric vector containing the entered likelihood for each state in \code{node}.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/API_Manuals/}: \code{h_node_get_entered_finding}.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\examples{
RHExample("buildAppleTreeNetwork")

# Compile the domain
compile(AppleTree)

# Set finding
set.finding(AppleTree, "Loses", c(1, 0))

# Get finding
get.finding(AppleTree, "Loses")
}

\keyword{programming}

