\name{get.finding}
\alias{get.finding}

\title{Get Finding}

\description{
Retrieve the entered or propagated finding from a node in an RHugin domain.
}

\usage{
get.finding(domain, node, type = c("entered", "propagated"))
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{node}{a character string specifying the name of the node from which the entered findings are to be retrieved.}
  \item{type}{a character string specifying whether the entered finding or the propagated finding is returned.}
}

\value{
  for discrete nodes: a numeric vector containing the entered likelihood for each state in \code{node}; for continuous nodes a single numeric value containing the entered finding.
}

\references{
HUGIN API Reference Manual \url{http://download.hugin.com/webdocs/manuals/api-manual.pdf}: \code{h_node_get_entered_finding}, \code{RHugin_node_get_entered_value}, \code{RHugin_node_get_propagated_finding} and \code{RHugin_node_get_propagated_value}.
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

\examples{
demo("apple", echo = FALSE)

# Compile the domain
compile(apple)

# Set finding
set.finding(apple, "Loses", c(1, 0))

# Get finding
get.finding(apple, "Loses")
}

\keyword{programming}


