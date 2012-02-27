\name{adapt}
\Rdversion{1.1}
\alias{adapt}

\title{Adapt}

\description{
Update (adapt) the conditional probability and experience tables in an RHugin domain.
}

\usage{
adapt(domain)
}

\arguments{
  \item{domain}{an RHugin domain.}
}

\details{
An adaptation step consists of entering and propagating evidence then updating (adapting) the conditional probability and experience tables in the domain.  The updating step is performed using this function.  The \code{adapt} function updates (adapts), for all discrete chance nodes of domain, the experience count (retrieval of experience) and the conditional probability distribution (dissemination of experience) for all parent configurations having a valid experience count and a valid fading factor.
}

\value{
a \code{NULL} value is invisibly returned.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/api-manuals}: \code{h_domain_adapt}.
}

\author{Kjell Konis \email{kjell.konis@me.com}}

\examples{
demo("apple", echo = FALSE)
## more to come ##
}

\keyword{programming}
