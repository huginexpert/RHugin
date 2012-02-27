\name{RHugin.control}
\alias{RHugin.control}

\title{RHugin Multiprocessing Control Parameters}

\description{
Set the concurrency level and grain size parameters in a domain.
}

\usage{
RHugin.control(domain, concurrency.level, grain.size)
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{concurrency.level}{optional: a positive integer value giving the concurrency level. The default is 1.}
  \item{grain.size}{optional: a positive integer value giving the grain size. The default is 20000.}
}

\details{
Thread creation in the Hugin Decision Engine is controlled by two parameters: the concurrency level and the grain size. The concurrency level specifies the maximum number of threads to create when performing a specific table operation.  The grain size specifies a lower limit on the size of the tasks performed by each thread.  The size of a task is roughly equal to the number of floating-point operations taken to perform it.
}

\value{
A list containing the current concurrency level and grain size. These values will be equal to those specified in the arguments when provided. This function can be called providing only the \code{domain} argument to retrieve the current parameters from the domain.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/api-manuals}: \code{h_domain_set_concurrency_level}, \code{h_domain_get_concurrency_level}, \code{h_domain_set_grain_size} and \code{h_domain_get_grain_size}.
}

\author{Kjell Konis \email{kjell.konis@me.com}}

\note{
In the current implementation of the Hugin Decision Engine (version 7.2), table operations for compressed domains are not threaded.
}

\keyword{programming}


