\name{retract}
\alias{retract}

\title{Retract Evidence}

\description{
Retract evidence from one or more nodes in an RHugin domain.
}

\usage{
retract(domain, nodes)
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{nodes}{an optional character vector specifying the names of the nodes for which evidence is to be retracted.}
}

\details{
The \code{nodes} argument is optional.  If only \code{domain} is given then evidence is retracted from all nodes.
}

\value{
a \code{NULL} value is invisibly returned.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/api-manuals}: \code{h_node_retract_findings}.
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

\examples{
demo("apple", echo = FALSE)

# Compile the domain
compile(apple)

# Select states
set.finding(apple, "Dry", "no")
set.finding(apple, "Loses", "yes")

# Propagate and get beliefs
propagate(apple)
get.belief(apple, "Sick")

# Retract evidence from Dry and propagate
retract(apple, "Dry")
propagate(apple)
get.belief(apple, "Sick")

# Retract all evidence and propagate
retract(apple)
propagate(apple)
get.belief(apple, "Sick")
}

\keyword{programming}


