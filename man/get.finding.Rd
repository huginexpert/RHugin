\name{get.finding}
\alias{get.finding}

\title{Get Entered Finding}

\description{
Retrieve the entered finding from a node in an RHugin domain.
}

\usage{
get.finding(domain, node)
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{node}{a character string specifying the name of the node from which the entered findings are to be retrieved.}
}

\value{
  for discrete nodes: a numeric vector containing the entered likelihood for each state in \code{node}; for continuous nodes a single numeric value containing the entered finding.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/API_Manuals/}: \code{h_node_get_entered_finding}.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\examples{
demo("buildAppleTreeNetwork", echo = FALSE)

# Compile the domain
compile(AppleTree)

# Set finding
set.finding(AppleTree, "Loses", c(1, 0))

# Get finding
get.finding(AppleTree, "Loses")
}

\keyword{programming}


