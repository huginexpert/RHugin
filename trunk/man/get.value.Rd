\name{get.value}
\alias{get.value}

\title{Get Value}

\description{
Evaluate the function associated with a real-valued function node and return the result.
}

\usage{
get.value(domain, node)
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{node}{a character string specifying the name of a real-valued function node.}
}

\value{
a single numeric value.
}

\references{
HUGIN API Reference Manual \url{http://download.hugin.com/webdocs/manuals/api-manual.pdf}: \code{h_node_get_value}.
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

\examples{
# Create a new domain
d <- hugin.domain()

# Add a function node to d
add.node(d, "fn", category = "function", kind = "other")

# Create a model for the function node
m <- get.model(d, "fn", character(0))
m$Expression <- "2"
set.model(d, "fn", m)

# Evaluate the function
get.value(d, "fn")
}

\keyword{programming}


